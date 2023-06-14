/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:56:40 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/14 21:18:54 by jihyeole         ###   ########.fr       */
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

void	env_lstdelone(t_env *lst)
{
	if (lst == NULL)
		return ;
	free(lst->key);
	free(lst->value);
	free(lst);
}

void	set_shlvl(t_env **env_lst)
{
	t_env	*lst;
	char	*num;
	int		n;

	lst = get_lst_by_key(*env_lst, "SHLVL");
	if (lst == NULL)
	{
		lst = env_lst_new("SHLVL=1");
		env_lst_add_back(env_lst, lst);
	}
	else
	{
		num = lst->value;
		if (!num && ft_strlen(num) > 4)
			lst->value = ft_strdup("1");
		else if (num[0] == '+' && check_num(&num[1]))
			lst->value = ft_itoa(ft_atoi(num) + 1);
		else if (check_num(num))
		{
			n = ft_atoi(num);
			if (n >= 0 && n < 999)
				lst->value = ft_itoa(n + 1);
			else if (n == 999)
				lst->value = ft_strdup("");
			else
				lst->value = ft_strdup("1");
		}
		else
			lst->value = ft_strdup("1");
	}
}

void	get_env_lst(t_env **env_lst, char **env)
{
	t_env	*new;
	int		i;

	i = 0;
	while (env[i])
	{
		new = env_lst_new(env[i]);
		env_lst_add_back(env_lst, new);
		++i;
	}
	set_shlvl(env_lst);
}
