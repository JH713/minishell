/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:33:01 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/05 04:36:22 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status;

t_info	*parse_command(char *command, t_env *env_lst)
{
	t_list	*list;
	t_info	*info;
	t_list	*temp;
	int		i;

	i = -1;
	list = split_command(command, 0, 0);
	if (list == NULL)
		return (NULL);
	temp = list;
	if (check_error(list))
	{
		ft_lstclear(&list, free);
		return (NULL);
	}
	info = malloc(sizeof(t_info));
	info->heredoc_num = 0;
	info->process_num = pipe_num(list) + 1;
	info->commands = (t_command *)malloc(sizeof(t_command) * info->process_num);
	while (++i < info -> process_num)
		list = put_command(info, &(info->commands[i]), list, env_lst);
	ft_lstclear(&temp, free);
	info->env = env_lst;
	return (info);
}

void	leaks(void)
{
	system("leaks minishell");
}

int	check_single_builtin(t_info *info)
{
	char	**command;

	if (info->process_num != 1) //프로세스 개수 1개 아니면 single 아님
		return (0);
	command = info->commands[0].command;
	if (command[0] == NULL)
		return (0);
	return (check_builtin(command));
}

void	init_redirect_fd(int *redirect_fd)
{
	int	i;

	i = 0;
	while (i < 257)
	{
		redirect_fd[i] = -1;
		++i;
	}
	redirect_fd[0] = 0;
	redirect_fd[1] = 1;
	redirect_fd[2] = 2;
}

int	is_fd_in_redirect_fd(int fd, int *redirect_fd)
{
	int	i;

	i = 0;
	while (redirect_fd[i] >= 0)
	{
		if (fd == redirect_fd[i])
			return (-1);
		++i;
	}
	return (i);
}

int	put_redirect_fd(t_redirect *redirect, int *redirect_fd)
{
	int	fd;
	int	i;

	while (redirect)
	{
		if (redirect->fd)
		{
			fd = fd_check_in_single_bulletin(redirect->fd);
			if (fd < 0)
				return (0); //free할거 하고
			i = is_fd_in_redirect_fd(fd, redirect_fd);
			if (i == -1)
				continue ;
			else
				redirect_fd[i] = fd;
		}
		redirect = redirect->next;
	}
	return (1);
}

void	duplicate_fd(int *redirect_fd, int *dup_fd)
{
	int	i;

	i = 0;
	while (redirect_fd[i] >= 0)
	{
		if (redirect_fd[i] == 0 || redirect_fd[i] == 1 || redirect_fd[i] == 2)
			dup_fd[i] = dup(redirect_fd[i]);
		else
			dup_fd[i] = -2;
		++i;
	}
}

void	restore_original_fd(int *redirect_fd, int *dup_fd)
{
	int	i;

	i = 0;
	while (redirect_fd[i] >= 0)
	{
		if (redirect_fd[i] == 0 || redirect_fd[i] == 1 || redirect_fd[i] == 2)
		{
			dup2(dup_fd[i], redirect_fd[i]);
			close(dup_fd[i]);
		}
		else
			close(redirect_fd[i]);
		++i;
	}
}

int	process_single_builtin(t_info *info)
{
	int			redirect_fd[257];
	int			dup_fd[257];
	int			i;
	t_command	cmd_struct;
	int			ret;

	init_redirect_fd(redirect_fd);
	init_redirect_fd(dup_fd);
	i = 0;
	while (i < info->process_num)
	{
		cmd_struct = info->commands[i];
		if (put_redirect_fd(cmd_struct.input, redirect_fd) == 0)
			return (0);
		if (put_redirect_fd(cmd_struct.output, redirect_fd) == 0)
			return (0);
		++i;
	}
	duplicate_fd(redirect_fd, dup_fd);
	ret = exec_single_builtin(info, &(info->env));
	unlink_heredocs(info);
	restore_original_fd(redirect_fd, dup_fd);
	if (ret == 1)
		exit_status = 0;
	free_info(info);
	return (1);
}

int	main(int argc, char *argv[], char **env)
{
	t_env		*env_lst;
	char		*command;
	t_info		*info;
	t_process	*process;

	atexit(leaks);
	(void)argv;
	init(argc, env, &env_lst, &command);
	while (1)
	{
		init_in_while(command);
		command = read_command();
		if (command == NULL)
			continue ;
		info = parse_command(command, env_lst);
		if (info == NULL)
			continue ;
		if (create_heredoc_temp(info) == 0)
			continue ;
		if (check_single_builtin(info))
		{
			if (process_single_builtin(info) == 0)
			{
				unlink_heredocs(info);
				free_info(info);
			}
			continue ;
		}
		process = (t_process *)malloc(sizeof(t_process) * info->process_num);
		create_pipe(process, info->process_num);
		fork_and_execute(process, info, &env_lst);
		wait_all_child(info->process_num, process);
		unlink_heredocs(info);
		free_info(info);
		free(process);
	}
}
