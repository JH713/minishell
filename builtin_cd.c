/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 23:33:19 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/13 17:45:44 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_no_args(t_env **env_lst, int *ret)
{
	t_env	*lst;

	lst = get_lst_by_key(*env_lst, "HOME");
	if (lst == NULL)
	{
		ft_putendl_fd("minishell: cd: HOME path not found", 2);
		g_exit_status = 1;
		*ret = 1;
		return ;
	}
	*ret = chdir(lst->value);
}

int	builtin_cd(char **command, t_env **env_lst, char **env)
{
	int		ret;
	char	*full_path;

	if (command[1] == NULL)
		cd_no_args(env_lst, &ret);
	else if (command[1][0] == '-')
		return (0);
	else if (command[1][0] == '/' || command[1][0] == '.')
		ret = chdir(command[1]);
	else
	{
		full_path = ft_strjoin("./", command[1]);
		ret = chdir(full_path);
		free(full_path);
	}
	if (ret == -1)
	{
		g_exit_status = 1;
		ft_putstr_fd("minishell: ", 2);
		perror("cd");
		return (-1);
	}
	free_env_arr(env);
	return (1);
}
