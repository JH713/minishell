/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 00:16:48 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/16 13:46:02 by jihyeole         ###   ########.fr       */
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
