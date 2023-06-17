/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 23:33:19 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/17 22:27:13 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_no_args(t_env **env_lst, int *ret)
{
	t_env	*lst;
	t_env	*oldpwd;

	lst = get_lst_by_key(*env_lst, "HOME");
	if (lst == NULL)
	{
		ft_putendl_fd("minishell: cd: HOME path not found", 2);
		g_exit_status = 1;
		*ret = 1;
		return ;
	}
	oldpwd = get_lst_by_key(*env_lst, "OLDPWD");
	if (oldpwd)
	{
		if (oldpwd->value)
			free(oldpwd->value);
		oldpwd->value = NULL;
		oldpwd->value = getcwd(oldpwd->value, 0);
	}
	*ret = chdir(lst->value);
}

int	builtin_cd(char **command, t_env **env_lst, char **env)
{
	int		ret;
	t_env	*oldpwd;

	if (command[1] == NULL)
		cd_no_args(env_lst, &ret);
	else if (command[1][0] == '-')
		return (0);
	else
	{
		oldpwd = get_lst_by_key(*env_lst, "OLDPWD");
		if (oldpwd)
		{
			if (oldpwd->value)
				free(oldpwd->value);
			oldpwd->value = NULL;
			oldpwd->value = getcwd(oldpwd->value, 0);
		}
		ret = chdir(command[1]);
	}
	free_env_arr(env);
	if (ret == -1)
		return (minishell_perror_not_exit("cd", 1));
	return (1);
}
