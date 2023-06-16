/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:56:40 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/16 14:08:10 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_lst_size(t_env *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		++size;
	}
	return (size);
}

char	*get_env_str(t_env *env_lst)
{
	char	*temp;
	char	*env_str;

	if (env_lst == NULL)
		return (NULL);
	temp = ft_strjoin(env_lst->key, "=");
	env_str = ft_strjoin(temp, env_lst->value);
	free(temp);
	return (env_str);
}

char	**env_lst_to_arr(t_env *env_lst)
{
	int		i;
	char	**env;

	env = (char **)malloc(sizeof(char *) * (env_lst_size(env_lst) + 1));
	i = 0;
	while (env_lst)
	{
		if (env_lst->value)
		{
			env[i] = get_env_str(env_lst);
			++i;
		}
		env_lst = env_lst->next;
	}
	env[i] = NULL;
	return (env);
}

void	set_oldpwd(t_env **env_lst)
{
	t_env	*lst;

	lst = get_lst_by_key(*env_lst, "OLDPWD");
	if (lst == NULL)
	{
		lst = env_lst_new("OLDPWD");
		env_lst_add_back(env_lst, lst);
	}
	else
	{
		if (lst->value)
			free(lst->value);
		lst->value = NULL;
	}
}
