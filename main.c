/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjki2 <hyunjki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:33:01 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/03 22:43:40 by hyunjki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info	*parse_command(char *command, t_env *env_lst)
{
	t_list	*list;
	t_info	*info;
	t_list	*temp;
	int		i;

	i = -1;
	list = split_command(command, 0, 0);
	if (list == NULL) //syntax error 시 return NULL;
		return (NULL);
	temp = list;
	if (check_error(list)) //syntax error 시 return NULL;
	{
		ft_lstclear(&list, free);
		return (NULL); //list 다 free해줘야함 
	}
	info = malloc(sizeof(t_info));
	if (!info)
		exit(1);
	info->heredoc_num = 0;
	info->process_num = pipe_num(list) + 1;
	info->commands = (t_command *)malloc(sizeof(t_command) * info->process_num);
	while (++i < info -> process_num)
		list = put_command(info, &(info->commands[i]), list, env_lst);
	ft_lstclear(&temp, free);
	return (info);
}

static void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit_status = 1;
}

void    free_env(t_env *env_lst)
{
    t_env   *temp;
    while (env_lst)
    {
        free(env_lst->key);
        free(env_lst->value);
        temp = env_lst;
        env_lst = env_lst->next;
        free(temp);
    }
}

void leaks(void)
{
	system("leaks minishell");
}

void	print_info(t_info *info)
{
	ft_printf("process_num = %d\n", info->process_num);
	ft_printf("heredoc_num = %d\n", info->heredoc_num);

	int i = 0;
	int j;
	t_command *command;
	t_redirect *input;
	t_redirect *output;
	while (i < info->process_num)
	{
		ft_printf("commands %d\n", i);
		j = 0;
		command = &(info->commands[i]);
		input = command->input;
		output = command->output;
		while (command->command[j])
		{
			ft_printf("%s\n", command->command[j]);
			j++;
		}
		while (input)
		{
			ft_printf("input\n");
			ft_printf("type: %d\n", input->type);
			ft_printf("fd: %s\n", input->fd);
			ft_printf("file: %s\n", input->file);
			input = input->next;
		}
		while (output)
		{
			ft_printf("output\n");
			ft_printf("type: %d\n", output->type);
			ft_printf("fd: %s\n", output->fd);
			ft_printf("file: %s\n", output->file);
			output = output->next;
		}
		++i;
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_env		*env_lst;
	char		*command;
	t_info		*info;
	t_process	*process;
	int			ret;

	atexit(leaks);
	init(argc, argv, env, &env_lst);
	command = NULL;
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		if (command)
			free(command);
		command = read_command();
		if (command == NULL)
			continue ;
		info = parse_command(command, env_lst);
		if (info == NULL)
			continue ;
		// print_info(info);
		if (create_heredoc_temp(info, env_lst) == 0)
		{
			unlink_heredocs(info);
			free_info(info);
			continue ;
		}
		signal(SIGINT, sigint_handler);
		if (info->process_num == 1)
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
