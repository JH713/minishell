/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 23:07:00 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/17 23:00:47 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_env_name(char **env, char *key, int *i, int *flag)
{
	if (check_env_name(key) == 0)
	{
		minishell_argstr_error("export", env[*i], \
		"not a valid identifier", 1);
		*flag = 0;
		++(*i);
		free(key);
		return (0);
	}
	return (1);
}

static void	update_or_add_env(t_env **env_lst, char **env, char *key, int i)
{
	t_env	*new;
	t_env	*curr;
	int		idx;

	curr = *env_lst;
	idx = get_first_idx(env[i], '=');
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(key) + 1) == 0)
		{
			if (idx == -1)
				break ;
			free(curr->value);
			curr->value = ft_substr(env[i], idx + 1, \
			ft_strlen(env[i]) - 1 - idx);
			break ;
		}
		curr = curr->next;
	}
	if (curr == NULL)
	{
		new = env_lst_new(env[i]);
		env_lst_add_back(env_lst, new);
	}
}

void	export_error(char *env, int *flag)
{
	minishell_argstr_error("export", env, "not a valid identifier", 1);
	*flag = 0;
}

static int	export_env(t_env **env_lst, char **env)
{
	int		i;
	int		idx;
	int		flag;
	char	*key;

	i = -1;
	flag = 1;
	while (env[i] && env[++i])
	{
		idx = get_first_idx(env[i], '=');
		if (idx == 0)
			export_error(env[i], &flag);
		else
		{
			if (idx == -1)
				key = ft_strdup(env[i]);
			else
				key = ft_substr(env[i], 0, idx);
			if (validate_env_name(env, key, &i, &flag) == 0)
				continue ;
			update_or_add_env(env_lst, env, key, i);
			free(key);
		}
	}
	return (flag);
}

int	builtin_export(char **command, t_env **env_lst, char **env)
{
	t_env	*sorted_lst;

	if (command[1] == NULL)
	{
		sorted_lst = get_sorted_lst(*env_lst);
		print_export_env(sorted_lst);
		free_sorted_lst(sorted_lst);
	}
	else
	{
		if (command[1][0] == '-')
			return (0);
		if (export_env(env_lst, &command[1]) == 0)
		{
			free_env_arr(env);
			return (-1);
		}
	}
	free_env_arr(env);
	return (1);
}
