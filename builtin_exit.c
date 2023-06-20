/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:44:20 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/20 18:01:29 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_with_minus(char **command, unsigned char *exit_num)
{
	if (ft_strlen(command[1]) > 20 || !check_num(&command[1][1]) \
	|| ft_atol(command[1]) > 0)
		minishell_arg_error(command[0], command[1], \
		"numeric argument required", 255);
	if (ft_strncmp(command[1], "-9223372036854775809", 21) == 0)
		minishell_arg_error(command[0], command[1], \
		"numeric argument required", 255);
	*exit_num = (unsigned char) ft_atol(command[1]);
}

void	exit_with_plus(char **command, unsigned char *exit_num)
{
	if (ft_strlen(command[1]) > 20 || !check_num(&command[1][1]) \
	|| ft_atol(command[1]) < 0)
		minishell_arg_error(command[0], command[1], \
		"numeric argument required", 255);
	if (ft_strncmp(command[1], "+9223372036854775808", 21) == 0)
		minishell_arg_error(command[0], command[1], \
		"numeric argument required", 255);
	*exit_num = (unsigned char) ft_atol(command[1]);
}

void	exit_without_sign(char **command, unsigned char *exit_num)
{
	if (ft_strlen(command[1]) > 19 || !check_num(command[1]) \
	|| ft_atol(command[1]) < 0)
		minishell_arg_error(command[0], command[1], \
		"numeric argument required", 255);
	if (ft_strncmp(command[1], "9223372036854775808", 20) == 0)
		minishell_arg_error(command[0], command[1], \
		"numeric argument required", 255);
	*exit_num = (unsigned char) ft_atol(command[1]);
}

void	builtin_exit(t_info *info, char **command)
{
	unsigned char	exit_num;

	exit_num = 0;
	unlink_heredocs(info);
	if (command[1])
	{
		if (command[2])
		{
			if (command[1][0] == '-')
				exit_with_minus(command, &exit_num);
			else if (command[1][0] == '+')
				exit_with_plus(command, &exit_num);
			else
				exit_without_sign(command, &exit_num);
			minishell_error(command[0], "too many arguments", 1);
		}
		if (command[1][0] == '-')
			exit_with_minus(command, &exit_num);
		else if (command[1][0] == '+')
			exit_with_plus(command, &exit_num);
		else
			exit_without_sign(command, &exit_num);
	}
	exit(exit_num);
}
