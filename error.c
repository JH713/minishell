/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:30:46 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/05 17:02:51 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_error_not_exit(char *cmd, char *err_msg, int exit_num)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err_msg, 2);
	g_exit_status = exit_num;
}

void	minishell_error(char *command, char *err_msg, int exit_num)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err_msg, 2);
	g_exit_status = exit_num;
	exit(exit_num);
}

void	minishell_arg_error(char *cmd, char *arg, char *msg, int exit_num)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	g_exit_status = exit_num;
	exit(exit_num);
}

void	minishell_argstr_error(char *cmd, char *arg, char *msg, int num)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd(msg, 2);
	g_exit_status = num;
}

void	minishell_perror(char *msg, int exit_num)
{
	ft_putstr_fd("minishell: ", 2);
	perror(msg);
	g_exit_status = exit_num;
	exit(exit_num);
}
