/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 00:16:48 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/01 00:17:19 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	exit_status;

static int	check_consecutive_pipes(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i] == ' ')
		--i;
	if (i < 0 || str[i] != '|')
		return (0);
	--i;
	while (i >= 0 && str[i] == ' ')
		--i;
	if (i < 0 || str[i] != '|')
		return (0);
	return (1);
}

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
	if (exit_status == 2)
	{
		exit_status = 130;
		printf("\n");
	}
	else if (exit_status == 3)
	{
		exit_status = 131;
		printf("Quit: 3\n");
	}
}

static void	handle_last_pipe(char **command)
{
	char	*add;
	char	*temp;

	while (last_char_without_whitespace(*command) == '|')
	{
		if (check_consecutive_pipes(*command))
			break ;
		add = readline("> ");
		temp = *command;
		*command = ft_strjoin(*command, " ");
		free(temp);
		temp = *command;
		*command = ft_strjoin(*command, add);
		free(temp);
		free(add);
	}
}

char	*read_command(void)
{
	char	*command;
	int		i;

	handle_exit_status();
	command = readline("minishell$ ");
	if (command == NULL)
	{
		ft_putstr_fd("\x1b[1A\033[11Cexit\n", 1);
		exit(0);
	}
	i = 0;
	while (command[i] == ' ')
		++i;
	if (command[i] == 0)
	{
		if (i > 0)
			add_history(command);
		free(command);
		return (NULL);
	}
	if (command[i] != '|')
		handle_last_pipe(&command);
	add_history(command);
	return (command);
}