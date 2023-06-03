/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjki2 <hyunjki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:42:16 by hyunjki2          #+#    #+#             */
/*   Updated: 2023/06/03 21:57:28 by hyunjki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_end(char *command, int i, char c)
{
	int	len;

	len = 1;
	i++;
	while (command[i])
	{
		if (command[i++] == c)
			return (len);
		len++;
	}
	return (0);
}

int	ft_strcmp(char	*s1, char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	return (1);
}

void	add_list(char *str, t_list **cmds)
{
	t_list	*new;

	new = ft_lstnew(str);
	ft_lstadd_back(cmds, new);
}

int	check_prev(char *command, int i, t_list *cmds)
{
	t_list	*temp;
	char	*c;
	int		k;

	k = 0;
	if (i - 1 >= 0 && ft_isdigit(command[i - 1]))
	{
		temp = ft_lstlast(cmds);
		c = temp -> content;
		while (c[k])
		{
			if (!ft_isdigit(c[k]))
				return (0);
			k++;
		}
		return (1);
	}
	return (0);
}
