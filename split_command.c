/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:39:04 by hyunjki2          #+#    #+#             */
/*   Updated: 2023/06/05 05:53:49 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	join_sep_to_fd(char *command, int start, int i, t_list **cmds)
{
	char	*sep;
	t_list	*last;
	char	*temp;

	while (command[i] && (command[i] == '<' || command[i] == '>'))
		i++;
	last = ft_lstlast(*cmds);
	sep = ft_substr(command, start, i - start);
	if (!check_sep(sep))
	{
		free(sep);
		return (-1);
	}
	temp = last -> content;
	last -> content = ft_strjoin(last -> content, sep);
	free(temp);
	free(sep);
	return (i);
}

int	find_sep(char *command, int start, int i, t_list **cmds)
{
	char	*sep;

	if (check_prev(command, i, *cmds))
	{
		i = join_sep_to_fd(command, start, i, cmds);
		if (i == -1)
			return (-1);
	}
	else
	{
		while (command[i] && (command[i] == '<' || command[i] == '>'))
				i++;
		sep = ft_substr(command, start, i - start);
		if (!check_sep(sep))
		{
			free(sep);
			return (-1);
		}
		add_list(sep, cmds);
	}
	return (i - start);
}

int	get_operator(char *command, int i, t_list **cmds, int *flag)
{
	int	start;
	int	ret;

	if (command[i] && (command[i] == '<' || command[i] == '>'))
	{
		start = i;
		if (*flag == 1)
			return (handle_consecutive_redirection_error(command, i));
		ret = find_sep(command, start, i, cmds);
		if (ret == -1)
			return (-1);
		i += ret;
		*flag = 1;
	}
	if (command[i] == '|')
	{
		if (*flag == 2 || *flag == 1)
		{
			error_m(0);
			return (-1);
		}
		add_list(ft_substr(command, i++, 1), cmds);
		*flag = 2;
	}
	return (i);
}

int	get_word(char *command, int i, t_list **cmds, int *flag)
{
	int	start;

	start = i;
	while (command[i] && is_not_sep(command[i]))
	{
		if (command[i] == '"' || command[i] == '\'')
			i = i + check_end(command, i, command[i]);
		i++;
	}
	add_list(ft_substr(command, start, i - start), cmds);
	*flag = 0;
	return (i);
}

t_list	*split_command(char *command, int i, int flag)
{
	t_list	*cmds;

	cmds = 0;
	while (command && command[i])
	{
		if (is_not_sep(command[i]))
			i = get_word(command, i, &cmds, &flag);
		else
		{
			while (command[i] && command[i] == ' ')
				i++;
			if (command[i] && (command[i] == '<' || command[i] == '>' \
					|| command[i] == '|'))
			{
				i = get_operator(command, i, &cmds, &flag);
				if (i == -1)
				{
					ft_lstclear(&cmds, free);
					return (NULL);
				}
			}
		}
	}
	return (cmds);
}
