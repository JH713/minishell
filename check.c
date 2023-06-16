/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:06:29 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/16 13:44:30 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fd_check(char *fd)
{
	int	fd_num;

	if (ft_strlen(fd) > 3)
		minishell_error(fd, strerror(9), 1);
	fd_num = ft_atoi(fd);
	if (fd_num >= 256)
		minishell_error(fd, strerror(9), 1);
	return (fd_num);
}

int	fd_check_in_single_bulletin(char *fd)
{
	int	fd_num;

	if (ft_strlen(fd) > 3)
	{
		minishell_error_not_exit(fd, strerror(9), 1);
		return (-1);
	}
	fd_num = ft_atoi(fd);
	if (fd_num >= 256)
	{
		minishell_error_not_exit(fd, strerror(9), 1);
		return (-1);
	}
	return (fd_num);
}

char	*check_file(char *command)
{
	struct stat	path_stat;

	if (access(command, F_OK) != 0)
		minishell_perror(command, 127);
	if (access(command, X_OK) != 0)
		minishell_perror(command, 126);
	if (stat(command, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		minishell_error(command, "is a directory", 126);
	return (ft_strdup(command));
}

char	*execute_check(char *command, char **path)
{
	int			i;
	char		*full_path;
	struct stat	path_stat;

	if (command[0] == '.' || command[0] == '/')
		return (check_file(command));
	i = 0;
	if (path)
	{
		while (path[i])
		{
			full_path = ft_strjoin(path[i], command);
			if (access(full_path, X_OK) == 0 && \
			stat(full_path, &path_stat) == 0 && S_ISREG(path_stat.st_mode))
				return (full_path);
			free(full_path);
			++i;
		}
	}
	minishell_error(command, "command not found", 127);
	return (NULL);
}
