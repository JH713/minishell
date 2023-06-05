/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 00:16:48 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/05 16:56:06 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	last_char_without_whitespace(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i] == ' ')
		--i;
	if (i < 0)
		return (0);
	return (str[i]);
}

static void	handle_exit_status(void)
{
	if (g_exit_status == 2)
	{
		g_exit_status = 130;
		printf("\n");
	}
	else if (g_exit_status == 3)
	{
		g_exit_status = 131;
		printf("Quit: 3\n");
	}
}

static int	is_whitespace_only(char *command)
{
	int	i;

	i = 0;
	while (command[i] == ' ')
		++i;
	if (command[i] == 0)
	{
		if (i > 0)
			add_history(command);
		free(command);
		return (1);
	}
	return (0);
}

char	*read_command(void)
{
	char	*command;

	handle_exit_status();
	command = readline("minishell$ ");
	if (command == NULL)
	{
		ft_putstr_fd("\x1b[1A\033[11Cexit\n", 1);
		exit(0);
	}
	if (is_whitespace_only(command))
		return (NULL);
	add_history(command);
	if (last_char_without_whitespace(command) == '|')
	{
		error_m(6);
		free(command);
		return (NULL);
	}
	return (command);
}
