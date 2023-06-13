/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 23:10:17 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/13 16:07:37 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_sorted_lst(t_env *sorted_lst)
{
	t_env	*temp;

	while (sorted_lst)
	{
		temp = sorted_lst;
		sorted_lst = sorted_lst->next;
		free(temp);
	}
}

void	print_export_env(t_env *sorted_lst)
{
	while (sorted_lst)
	{
		ft_printf("declare -x %s=\"%s\"\n", sorted_lst->key, sorted_lst->value);
		sorted_lst = sorted_lst->next;
	}
}

static t_env	*dup_env_lst(t_env *env_lst)
{
	t_env	*new_lst;

	new_lst = (t_env *)malloc(sizeof(t_env));
	new_lst->key = env_lst->key;
	new_lst->value = env_lst->value;
	new_lst->next = NULL;
	return (new_lst);
}

static void	insert_sorted_env(t_env **sorted_lst, t_env	*new)
{
	t_env	*prev;
	t_env	*curr;

	curr = *sorted_lst;
	while (curr)
	{
		if (jh_strcmp(new->key, curr->key) < 0)
		{
			new->next = curr;
			if (curr == *sorted_lst)
				*sorted_lst = new;
			else
				prev->next = new;
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL)
		prev->next = new;
}

t_env	*get_sorted_lst(t_env *env_lst)
{
	t_env	*sorted_lst;
	t_env	*new;

	if (env_lst == NULL)
		return (NULL);
	sorted_lst = dup_env_lst(env_lst);
	env_lst = env_lst->next;
	while (env_lst)
	{
		new = dup_env_lst(env_lst);
		insert_sorted_env(&sorted_lst, new);
		env_lst = env_lst->next;
	}
	return (sorted_lst);
}
