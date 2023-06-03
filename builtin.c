/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:09:47 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/03 17:35:54 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int exit_status;

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

int	jh_strcmp(char	*s1, char *s2)
{
	size_t			idx;
	unsigned char	*c1;
	unsigned char	*c2;

	idx = 0;
	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (*(c1 + idx) == *(c2 + idx))
	{
		if (*(c1 + idx) == 0)
			return (0);
		++idx;
	}
	return (*(c1 + idx) - *(c2 + idx));
}

void	print_export_env(t_env *sorted_lst)
{
	while (sorted_lst)
	{
		ft_printf("declare -x %s=\"%s\"\n", sorted_lst->key, sorted_lst->value);
		sorted_lst = sorted_lst->next;
	}
}

t_env	*dup_env_lst(t_env *env_lst)
{
	t_env	*new_lst;

	new_lst = (t_env *)malloc(sizeof(t_env));
	new_lst->key = env_lst->key;
	new_lst->value = env_lst->value;
	new_lst->next = NULL;
	return (new_lst);
}

t_env	*get_sorted_lst(t_env *env_lst)
{
	t_env	*sorted_lst;
	t_env	*prev;
	t_env	*curr;
	t_env	*new;

	if (env_lst == NULL)
		return (NULL);
	sorted_lst = dup_env_lst(env_lst);
	env_lst = env_lst->next;
	while (env_lst)
	{
		if (ft_strncmp(env_lst->key, "_", 2) == 0)
		{
			env_lst = env_lst->next;
			continue ;
		}
		new = dup_env_lst(env_lst);
		curr = sorted_lst;
		while (curr)
		{
			if (jh_strcmp(new->key, curr->key) < 0)
			{
				new->next = curr;
				if (curr == sorted_lst)
					sorted_lst = new;
				else
					prev->next = new;
				break ;
			}
			prev = curr;
			curr = curr->next;
		}
		if (curr == NULL)
			prev->next = new;
		env_lst = env_lst->next;
	}
	return (sorted_lst);
}

int	check_option_n(char *str)
{
	if (*str != '-')
		return (0);
	str++;
	while (*str == 'n')
		str++;
	if (*str == 0)
		return (1);
	return (0);
}

int	export_env(t_env **env_lst, char **env)
{
	t_env	*new;
	t_env	*curr;
	int		i;
	int		idx;
	int		flag;

	i = 0;
	flag = 1;
	while (env[i])
	{
		curr = *env_lst;
		idx = get_first_idx(env[i], '=');
		char *key = ft_substr(env[i], 0, idx);
		if (check_env_name(key) == 0)
		{
			minishell_argstr_error("unset", env[i], "not a valid identifier", 1);
			flag = 0;
			++i;
			continue ;
		}
		while (curr)
		{
			if (ft_strncmp(curr->key, env[i], idx) == 0)
			{
				free(curr->value);
				curr->value = ft_substr(env[i], idx + 1, ft_strlen(env[i]) - 1 - idx);
				break ;
			}
			curr = curr->next;
		}
		if (curr == NULL)
		{
			new = env_lst_new(env[i]);
			env_lst_add_back(env_lst, new);
		}
		++i;
	}
	return (flag);
}

int check_env_name(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (0);
	while (ft_isalnum(str[i]) || str[i] == '_')
		++i;
	if (str[i] != 0)
		return (0);
	return (1);
}

void    free_env_arr(char **env)
{
    int i;
    i = 0;
    while (env[i])
    {
        free(env[i]);
        ++i;
    }
    free(env);
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
	{
		unsigned char exit_num;
		exit_num = 0;
		unlink_heredocs(info);
		if (command[1])
		{
			if (command[2])
				minishell_error(command[0], "too many arguments", 1);
			if (!check_num(command[1]))
				minishell_arg_error(command[0], command[1], "numeric argument required", 255);
			exit_num = (unsigned char)ft_atoi(command[1]);
		}
		exit(exit_num);
	}
	else if (ft_strncmp(command[0], "env", 4) == 0 && command[1] == NULL)
	{
		print_env(env, env_num);
		return (1);
	}
	else if (ft_strncmp(command[0], "export", 7) == 0)
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
			int i = 1;
			int idx; 
			while (command[i])
			{
				idx = get_first_idx(command[i], '=');
				if (idx == -1 | command[i][idx + 1] == 0)
				{
					minishell_error_not_exit(command[0], "argument must be in format of key=value", 1);
					return (-1);
				}
				++i;
			}
			if (export_env(env_lst, &command[1]) == 0)
				return (-1);
		}
		free_env_arr(env);
		return (1);
	}
	else if (ft_strncmp(command[0], "unset", 6) == 0) // 환경변수 이름에 알파벳이랑 _만 들어가도록
	{
		if (command[1])
		{
			if (command[1][0] == '-')
				return (0);
			if (env_lst_unset(env_lst, &command[1]) == 0)
				return (-1);
		}
		free_env_arr(env);
		return (1);
	}
	else if (ft_strncmp(command[0], "pwd", 4) == 0)
	{
		if (command[1] && command[1][0] == '-')
			return (0);
		char	*buf = NULL;
		buf = getcwd(buf, 0);
		ft_printf("%s\n", buf);
		free_env_arr(env);
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
		free_env_arr(env);
				exit_status = 1;
				return (1);
			}
			ret = chdir(lst->value);
		}
		else if (command[1][0] == '-')
			return (0);
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
		free_env_arr(env);
		return (1);
	}
	else if (ft_strncmp(command[0], "echo", 5) == 0)
	{
		int i;
		if (command[1])
		{
			if (check_option_n(command[1]))
			{
				int i = 2;
				while (check_option_n(command[i]))
					++i;
				while (command[i])
				{
					ft_putstr_fd(command[i], 1);
					if (command[i + 1] != NULL)
						ft_putchar_fd(' ', 1);
					++i;
				}
			}
			else if (command[1][0] == '-')
				return (0);
			else
			{
				i = 1;
				while (command[i])
				{
					ft_putstr_fd(command[i], 1);
					if (command[i + 1] != NULL)
						ft_putchar_fd(' ', 1);
					++i;
				}
				ft_printf("\n");
			}
		}
		else
			ft_printf("\n");
		free_env_arr(env);
		return (1);
	}
	return (0);
}
