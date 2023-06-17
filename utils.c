/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:56:21 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/17 23:46:27 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_first_idx(char *str, char c)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == c)
			return (idx);
		++idx;
	}
	return (-1);
}

char	**get_path(t_env *env_lst)
{
	char	**path;
	int		i;
	char	*temp;

	while (env_lst && ft_strncmp(env_lst->key, "PATH", 5) != 0)
		env_lst = env_lst->next;
	if (env_lst)
		path = ft_split(env_lst->value, ':');
	else
		return (NULL);
	i = 0;
	while (path[i])
	{
		temp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(temp);
		++i;
	}
	return (path);
}

char	*get_temp_name(void)
{
	char	*name;
	char	*num_str;
	int		num;
	int		ret;

	num = 1;
	ret = 0;
	while (1)
	{
		num_str = ft_itoa(num);
		name = ft_strjoin("/tmp/temp", num_str);
		free(num_str);
		ret = access(name, F_OK);
		if (ret == -1)
			break ;
		free(name);
		num++;
	}
	return (name);
}

void	cleanup_memory(t_info *info, t_process *process)
{
	unlink_heredocs(info);
	free_info(info);
	free(process);
}
