/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 06:08:16 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/19 18:00:59 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redirect_fd(int *redirect_fd)
{
	int	i;

	i = 0;
	while (i < 257)
	{
		redirect_fd[i] = -1;
		++i;
	}
	redirect_fd[0] = 0;
	redirect_fd[1] = 1;
	redirect_fd[2] = 2;
}

static int	is_fd_in_redirect_fd(int fd, int *redirect_fd)
{
	int	i;

	i = 0;
	while (redirect_fd[i] >= 0)
	{
		if (fd == redirect_fd[i])
			return (-1);
		++i;
	}
	return (i);
}

int	put_redirect_fd(t_redirect *re, int *redirect_fd, t_info *info)
{
	int	fd;
	int	i;

	while (re)
	{
		if (re->fd)
		{
			fd = fd_check_in_single_bulletin(re->fd);
			if (fd < 0)
			{
				unlink_heredocs(info);
				free_info(info);
				return (0);
			}
			i = is_fd_in_redirect_fd(fd, redirect_fd);
			if (i == -1)
				continue ;
			else
				redirect_fd[i] = fd;
		}
		re = re->next;
	}
	return (1);
}

void	duplicate_fd(int *redirect_fd, int *dup_fd)
{
	int	i;

	i = 0;
	while (redirect_fd[i] >= 0)
	{
		if (redirect_fd[i] == 0 || redirect_fd[i] == 1 || redirect_fd[i] == 2)
			dup_fd[i] = dup(redirect_fd[i]);
		else
			dup_fd[i] = -2;
		++i;
	}
}

void	restore_original_fd(int *redirect_fd, int *dup_fd)
{
	int	i;

	i = 0;
	while (redirect_fd[i] >= 0)
	{
		if (redirect_fd[i] == 0 || redirect_fd[i] == 1 || redirect_fd[i] == 2)
		{
			dup2(dup_fd[i], redirect_fd[i]);
			close(dup_fd[i]);
		}
		else
			close(redirect_fd[i]);
		++i;
	}
}
