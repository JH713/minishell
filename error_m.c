/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_m.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:17:55 by hyunjki2          #+#    #+#             */
/*   Updated: 2023/06/16 13:45:30 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	error_m(int c)
{
	if (c == 0)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		g_exit_status = 258;
	}
	else if (c == 6)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
		g_exit_status = 258;
	}
	else
		printf("Error%d\n", c);
}

void	error_m1(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	g_exit_status = 258;
}

void	print_error(char *msg, int status)
{
	if (status == 0)
		perror(msg);
	else if (status == 1)
		ft_putendl_fd(msg, 2);
	g_exit_status = 1;
	exit(1);
}

void	print_error_not_exit(char *msg, int status)
{
	if (status == 0)
		perror(msg);
	else if (status == 1)
		ft_putendl_fd(msg, 2);
	g_exit_status = 1;
}

int	minishell_perror_not_exit(char *msg, int exit_num)
{
	ft_putstr_fd("minishell: ", 2);
	perror(msg);
	g_exit_status = exit_num;
	return (-1);
}
