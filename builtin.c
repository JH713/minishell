/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:09:47 by jihyeole          #+#    #+#             */
/*   Updated: 2023/05/18 00:37:17 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int exit_status;

int	builtin_func(char **command, t_env **env_lst)
{
	char	**env;
	int		env_num;

	env = env_lst_to_arr(*env_lst);
	env_num = env_lst_size(*env_lst);
	if (ft_strncmp(command[0], "exit", 5) == 0 && command[1] == NULL)
		exit(0);
	else if (ft_strncmp(command[0], "env", 4) == 0 && command[1] == NULL)
	{
		print_env(env, env_num);
		return (1);
	}
	else if (ft_strncmp(command[0], "export", 7) == 0 && command[1])
	{
		get_env_lst(env_lst, &command[1]);
		return (1);
	}
	else if (ft_strncmp(command[0], "unset", 6) == 0 && command[1])
	{
		env_lst_unset(env_lst, &command[1]);
		return (1);
	}
	else if (ft_strncmp(command[0], "pwd", 4) == 0 && command[1] == NULL)
	{
		char	*buf = NULL;
		buf = getcwd(buf, 0);
		ft_printf("%s\n", buf);
		free(buf);
		return (1);
	}
	else if (ft_strncmp(command[0], "cd", 3) == 0)
	{
		int ret;
		if (command[1] == NULL)
		{
			t_env *lst;
			lst = get_lst_by_key(*env_lst, "HOME");
			if (lst == NULL)
			{
				ft_putendl_fd("minishell: cd: HOME path not found", 2);
				exit_status = 1;
				return (1);
			}
			ret = chdir(lst->value);
		}
		else if (command[1][0] == '/' || command[1][0] == '.')
			ret = chdir(command[1]);
		else
		{
			char *full_path = NULL;
			full_path = ft_strjoin("./", command[1]);
			ret = chdir(full_path);
			free(full_path);
		}
		if (ret == -1)
		{
			exit_status = 1;
			ft_putstr_fd("minishell: ", 2);
			perror("cd");
		}
		return (1);
	}
	else if (ft_strncmp(command[0], "echo", 5) == 0 && ft_strncmp(command[1], "-n", 3) == 0)
	{
		if (command[2] != NULL)
			ft_printf("%s", command[2]);
		return (1);
	}
	return (0);
}
