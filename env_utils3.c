/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:49:34 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/05 17:49:49 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_variable(t_env **env_lst, char **str, int i)
{
	t_env	*lst;
	t_env	*prev;

	lst = *env_lst;
	while (lst)
	{
		if (ft_strncmp(lst->key, str[i], (ft_strlen(lst->key) + 1)) == 0)
		{
			if (lst == *env_lst)
				*env_lst = NULL;
			else
				prev->next = lst->next;
			env_lstdelone(lst);
			break ;
		}
		prev = lst;
		lst = lst->next;
	}
}

int	env_lst_unset(t_env **env_lst, char **str)
{
	int		i;
	int		flag;

	i = -1;
	flag = 1;
	while (str[++i])
	{
		if (ft_strncmp(str[i], "_", 2) == 0)
		{
			continue ;
		}
		if (check_env_name(str[i]) == 0)
		{
			minishell_argstr_error("unset", str[i], \
			"not a valid identifier", 1);
			flag = 0;
			continue ;
		}
		remove_env_variable(env_lst, str, i);
	}
	return (flag);
}
