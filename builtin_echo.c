/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 23:01:27 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/05 23:03:27 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_option_n(char *str)
{
	if (*str != '-')
		return (0);
	str++;
	while (*str == 'n')
		str++;
	if (*str == 0)
		return (1);
	return (0);
}

static void	echo_option_n(char **command)
{
	int	i;

	i = 2;
	while (check_option_n(command[i]))
		++i;
	while (command[i])
	{
		ft_putstr_fd(command[i], 1);
		if (command[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		++i;
	}
}

static void	echo_no_option(char **command)
{
	int	i;

	i = 1;
	while (command[i])
	{
		ft_putstr_fd(command[i], 1);
		if (command[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		++i;
	}
	ft_printf("\n");
}

int	builtin_echo(char **command, char **env)
{
	if (command[1])
	{
		if (check_option_n(command[1]))
			echo_option_n(command);
		else if (command[1][0] == '-')
			return (0);
		else
			echo_no_option(command);
	}
	else
		ft_printf("\n");
	free_env_arr(env);
	return (1);
}
