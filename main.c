/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:33:01 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/16 14:38:56 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	print_maenggu(void)
{
	int		fd;
	size_t	length;
	char	buff[500001];

	fd = open("maenggu", O_RDONLY);
	length = read(fd, buff, 500000);
	write(1, buff, length);
	close(fd);
}

static t_info	*parse_command(char *command, t_env *env_lst)
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

static void	clear_last_arg(t_info *info, t_env **env_lst)
{
	t_env	*lst;
	char	*tmp;

	if (info->process_num != 1)
	{
		lst = get_lst_by_key(*env_lst, "_");
		tmp = lst->value;
		lst->value = ft_strdup("");
		if (tmp)
			free(tmp);
		return ;
	}
}

static void	set_last_arg(t_info *info, t_env **env_lst)
{
	t_env	*lst;
	char	*value;
	char	*tmp;
	int		j;

	value = NULL;
	clear_last_arg(info, env_lst);
	if (info->process_num == 1)
	{
		j = 0;
		while (info->commands[0].command[j])
		{
			value = info->commands[0].command[j];
			++j;
		}
		lst = get_lst_by_key(*env_lst, "_");
		tmp = lst->value;
		if (value == NULL)
			lst->value = ft_strdup("");
		else
			lst->value = ft_strdup(value);
		if (tmp)
			free(tmp);
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_env		*env_lst;
	char		*command;
	t_info		*info;
	t_process	*process;

	env_lst = init(argc, argv, env, &command);
	while (1)
	{
		init_in_while(command);
		command = read_command();
		info = parse_command(command, env_lst);
		if (info == NULL || create_heredoc_temp(info) == 0)
			continue ;
		set_last_arg(info, &env_lst);
		if (check_single_builtin(info))
		{
			process_single_builtin(info);
			continue ;
		}
		process = (t_process *)malloc(sizeof(t_process) * info->process_num);
		if (!create_pipe(process, info))
			continue ;
		fork_and_execute(process, info, &env_lst);
		wait_all_child(info, process);
	}
}
