/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:09:47 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/16 11:44:35 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtin_env(char **env, int env_num)
{
	print_env(env, env_num);
	free_env_arr(env);
	return (1);
}

static int	builtin_pwd(char **command, char **env)
{
	char	*buf;

	if (command[1] && command[1][0] == '-')
		return (0);
	buf = NULL;
	buf = getcwd(buf, 0);
	ft_printf("%s\n", buf);
	free_env_arr(env);
	free(buf);
	return (1);
}

static int	builtin_unset(char **command, t_env **env_lst, char **env)
{
	if (command[1])
	{
		if (command[1][0] == '-')
			return (0);
		if (env_lst_unset(env_lst, &command[1]) == 0)
		{
			free_env_arr(env);
			return (-1);
		}
	}
	free_env_arr(env);
	return (1);
}

int	builtin_func(t_info *info, char **command, t_env **env_lst)
{
	char	**env;
	int		env_num;

	if (command[0] == NULL)
		return (0);
	env = env_lst_to_arr(*env_lst);
	env_num = env_lst_size(*env_lst);
	if (ft_strncmp(command[0], "exit", 5) == 0)
		builtin_exit(info, command);
	else if (ft_strncmp(command[0], "env", 4) == 0 && command[1] == NULL)
		return (builtin_env(env, env_num));
	else if (ft_strncmp(command[0], "export", 7) == 0)
		return (builtin_export(command, env_lst, env));
	else if (ft_strncmp(command[0], "unset", 6) == 0)
		return (builtin_unset(command, env_lst, env));
	else if (ft_strncmp(command[0], "pwd", 4) == 0)
		return (builtin_pwd(command, env));
	else if (ft_strncmp(command[0], "cd", 3) == 0)
		return (builtin_cd(command, env_lst, env));
	else if (ft_strncmp(command[0], "echo", 5) == 0)
		return (builtin_echo(command, env));
	free_env_arr(env);
	return (0);
}
