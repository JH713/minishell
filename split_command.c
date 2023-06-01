/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjki2 <hyunjki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:39:04 by hyunjki2          #+#    #+#             */
/*   Updated: 2023/06/01 20:51:21 by hyunjki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	find_sep(char *command, int start, int i, t_list **cmds)
{
	char	*sep;
	t_list	*last;
	char	*temp;

	if (check_prev(command, i, *cmds))
	{
		while (command[i] && (command[i] == '<' || command[i] == '>'))
			i++;
		last = ft_lstlast(*cmds);
		sep = ft_substr(command, start, i - start);
		if (!check_sep(sep))
			return (-1);
		temp = last -> content; //이전꺼 free?
		last -> content = ft_strjoin(last -> content, sep);
		free(temp);
	}
	else
	{
		while (command[i] && (command[i] == '<' || command[i] == '>'))
				i++;
		sep = ft_substr(command, start, i - start);
		if (!check_sep(sep))
			return (-1);
		add_list(sep, cmds);
	}
	return (i - start);
}

int	handle_consecutive_redirection_error(char *command, int i)
{
	if (!command[i + 1] || command[i + 1] != command[i])
		error_m1(ft_substr(&command[i], 0, 1));
	else
		error_m1(ft_substr(&command[i], 0, 2));
	return (-1);
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

t_list	*split_command(char *command)
{
	t_list	*cmds;
	int		i;
	int		flag;

	cmds = 0;
	i = 0;
	flag = 0;
	while (command[i])
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
					return (NULL); // list free하기? 
				}
			}
		}
	}
	return (cmds);
}
