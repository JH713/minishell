/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:33:01 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/05 15:55:36 by jihyeole         ###   ########.fr       */
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

	// atexit(leaks);
	(void)argv;
	init(argc, env, &env_lst, &command);
	while (1)
	{
		init_in_while(command);
		command = read_command();
		info = parse_command(command, env_lst);
		// print_info(info);
		if (info == NULL || create_heredoc_temp(info) == 0)
			continue ;
		if (check_single_builtin(info))
		{
			process_single_builtin(info);
			continue ;
		}
		process = (t_process *)malloc(sizeof(t_process) * info->process_num);
		create_pipe(process, info->process_num);
		fork_and_execute(process, info, &env_lst);
		wait_all_child(info->process_num, process);
		cleanup_memory(info, process);
	}
}
