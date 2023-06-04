/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:33:01 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/05 00:11:58 by jihyeole         ###   ########.fr       */
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

// void	leaks(void)
// {
// 	system("leaks minishell");
// }

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

int	main(int argc, char *argv[], char **env)
{
	t_env		*env_lst;
	char		*command;
	t_info		*info;
	t_process	*process;
	int			ret;

	// atexit(leaks);
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
			int		stdin_dup;
			int		stdout_dup;
			int		stderr_dup;
			stdin_dup = dup(0);
			stdout_dup = dup(1);
			stderr_dup = dup(2);
			ret = exec_single_builtin(info, &env_lst);
			if (ret == 1)
			{
				unlink_heredocs(info);
				dup2(stdin_dup, 0);
				dup2(stdout_dup, 1);
				dup2(stderr_dup, 2);
				close(stdin_dup);
				close(stdout_dup);
				close(stderr_dup);
				exit_status = 0;
				free_info(info);
				continue ;
			}
			else if (ret == -1)
			{
				unlink_heredocs(info);
				dup2(stdin_dup, 0);
				dup2(stdout_dup, 1);
				dup2(stderr_dup, 2);
				close(stdin_dup);
				close(stdout_dup);
				close(stderr_dup);
				free_info(info);
				continue ;
			}
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
