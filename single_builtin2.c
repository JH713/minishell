/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_builtin2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:45:06 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/18 00:40:07 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_num(char *num)
{
	if (*num == '-' && *num)
		num++;
	while (*num)
	{
		if (!ft_isdigit(*num))
			return (0);
		num++;
	}
	return (1);
}

static int	exec_single_exit(t_info *info, char **cmd)
{
	unsigned char	exit_num;

	ft_putendl_fd("exit", 1);
	exit_num = 0;
	if (cmd[1])
	{
		if (cmd[2])
		{
			minishell_error_not_exit(cmd[0], "too many arguments", 1);
			return (-1);
		}
		unlink_heredocs(info);
		if (cmd[1][0] == '-')
			exit_with_minus(cmd, &exit_num);
		else if (cmd[1][0] == '+')
			exit_with_plus(cmd, &exit_num);
		else
			exit_without_sign(cmd, &exit_num);
	}
	else
		unlink_heredocs(info);
	exit(exit_num);
}

int	exec_single_builtin(t_info *info, t_env **env_lst)
{
	char			**cmd;

	cmd = info->commands[0].command;
	if (!redirect_process2(NULL, info, 0))
		return (-1);
	if (ft_strncmp(cmd[0], "exit", 5) == 0)
	{
		exec_single_exit(info, cmd);
		return (-1);
	}
	return (builtin_func(info, cmd, env_lst));
}
