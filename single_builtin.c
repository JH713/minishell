/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 06:05:23 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/13 17:42:57 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char **command)
{
	if (ft_strncmp(command[0], "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(command[0], "env", 4) == 0 && command[1] == NULL)
		return (1);
	else if (ft_strncmp(command[0], "export", 7) == 0)
	{
		if (command[1] && command[1][0] == '-')
			return (0);
		return (1);
	}
	else if (ft_strncmp(command[0], "unset", 6) == 0)
	{
		if (command[1] && command[1][0] == '-')
			return (0);
		return (1);
	}
	return (0);
}

int	check_builtin2(char **command)
{
	if (ft_strncmp(command[0], "pwd", 4) == 0)
	{
		if (command[1] && command[1][0] == '-')
			return (0);
		return (1);
	}
	else if (ft_strncmp(command[0], "cd", 3) == 0)
	{
		if (command[1] && command[1][0] == '-')
			return (0);
		return (1);
	}
	else if (ft_strncmp(command[0], "echo", 5) == 0)
	{
		if (command[1])
		{
			if (ft_strncmp(command[1], "-n", 3) == 0)
				return (1);
			else if (command[1][0] == '-')
				return (0);
		}
		return (1);
	}
	return (0);
}

int	check_single_builtin(t_info *info)
{
	char	**command;
	int		is_builtin;

	if (info->process_num != 1)
		return (0);
	command = info->commands[0].command;
	if (command[0] == NULL)
		return (0);
	is_builtin = 0;
	if (check_builtin(command) || check_builtin2(command))
		is_builtin = 1;
	return (is_builtin);
}

void	process_single_builtin(t_info *info)
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
		if (put_redirect_fd(cmd_struct.input, redirect_fd, info) == 0)
			return ;
		if (put_redirect_fd(cmd_struct.output, redirect_fd, info) == 0)
			return ;
		++i;
	}
	duplicate_fd(redirect_fd, dup_fd);
	ret = exec_single_builtin(info, &(info->env));
	unlink_heredocs(info);
	restore_original_fd(redirect_fd, dup_fd);
	if (ret == 1)
		g_exit_status = 0;
	free_info(info);
}
