/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_builtin2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:45:06 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/15 19:27:04 by jihyeole         ###   ########.fr       */
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
		{
			if (ft_strlen(cmd[1]) > 20 || !check_num(&cmd[1][1]) || ft_atol(cmd[1]) > 0)
				minishell_arg_error(cmd[0], cmd[1], \
				"numeric argument required", 255);
			if (ft_strncmp(cmd[1], "-9223372036854775809", 21) == 0)
				minishell_arg_error(cmd[0], cmd[1], \
				"numeric argument required", 255);
			exit_num = (unsigned char) ft_atol(cmd[1]);
		}
		else if (cmd[1][0] == '+')
		{
			if (ft_strlen(cmd[1]) > 20 || !check_num(&cmd[1][1]) || ft_atol(cmd[1]) < 0)
				minishell_arg_error(cmd[0], cmd[1], \
				"numeric argument required", 255);
			if (ft_strncmp(cmd[1], "+9223372036854775808", 21) == 0)
				minishell_arg_error(cmd[0], cmd[1], \
				"numeric argument required", 255);
			exit_num = (unsigned char) ft_atol(cmd[1]);
		}
		else
		{
			if (ft_strlen(cmd[1]) > 19 || !check_num(cmd[1]) || ft_atol(cmd[1]) < 0)
				minishell_arg_error(cmd[0], cmd[1], \
				"numeric argument required", 255);
			if (ft_strncmp(cmd[1], "9223372036854775808", 20) == 0)
				minishell_arg_error(cmd[0], cmd[1], \
				"numeric argument required", 255);
			exit_num = (unsigned char) ft_atol(cmd[1]);
		}
	}
	else
		unlink_heredocs(info);
	exit(exit_num);
}

int	exec_single_builtin(t_info *info, t_env **env_lst)
{
	char			**cmd;

	cmd = info->commands[0].command;
	redirect_process(NULL, info, 0);
	if (ft_strncmp(cmd[0], "exit", 5) == 0)
	{
		exec_single_exit(info, cmd);
		return (-1);
	}
	return (builtin_func(info, cmd, env_lst));
}
