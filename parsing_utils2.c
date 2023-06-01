/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjki2 <hyunjki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:40:36 by hyunjki2          #+#    #+#             */
/*   Updated: 2023/06/01 19:24:17 by hyunjki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	check_error(t_list *list)
{
	int		flag;
	char	*c;

	flag = 0;
	c = list -> content;
	if (ft_strcmp(c, "|"))
	{
		error_m(0);
		return (1);
	}
	c = ft_lstlast(list)->content;
	if (ft_strcmp(c, "<") || ft_strcmp(c, ">") || \
				ft_strcmp(c, "<<") || ft_strcmp(c, ">>"))
	{
		error_m(6);
		return (1);
	}
	return (0);
}

int	pipe_num(t_list	*list)
{
	t_list	*temp;
	int		num;

	temp = list;
	num = 0;
	while (temp)
	{
		if (ft_strcmp(temp->content, "|"))
			num++;
		temp = temp -> next;
	}
	return (num);
}

void	add_last(t_redirect **rd, t_redirect *new)
{
	t_redirect	*temp;

	if (new == NULL)
		return ;
	if (*rd == NULL)
		*rd = new;
	else
	{
		temp = *rd;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

t_redirect	*malloc_redirect(int type, char *fd, char *file)
{
	t_redirect	*new;

	new = malloc(sizeof(t_redirect));
	if (!new)
		exit(1);
	new -> type = type;
	new -> fd = fd;
	new -> file = file;
	new -> next = 0;
	return (new);
}

int	check_if_pair(char	*content, char quotes)
{
	while (*content)
	{
		if (*content == quotes)
			return (1);
		content++;
	}
	return (0);
}

