/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_m.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjki2 <hyunjki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:17:55 by hyunjki2          #+#    #+#             */
/*   Updated: 2023/06/04 15:55:38 by hyunjki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	error_m(int c)
{
	if (c == 0)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		exit_status = 258;
	}
	else if (c == 6)
	{
		ft_putendl_fd("minishell: syntax error near unexpected \
		token `newline'", 2);
		exit_status = 258;
	}
	else
		printf("Error%d\n", c);
}

void	error_m1(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	exit_status = 258;
}
