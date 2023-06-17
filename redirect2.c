/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 22:46:37 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/18 00:51:51 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_input_file2(t_redirect *input)
{
	int		fd;
	int		input_fd;
	char	*filepath;

	if (input->fd == NULL)
		input_fd = 0;
	else
		input_fd = fd_check(input->fd);
	if (input->file[0] != '/')
		filepath = ft_strjoin("./", input->file);
	else
		filepath = ft_strdup(input->file);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		minishell_perror_not_exit(input->file, 1);
	free(filepath);
	dup2(fd, input_fd);
	close(fd);
	if (fd == -1)
		return (0);
	else
		return (1);
}

static int	redirect_output_file2(t_redirect *output)
{
	int		fd;
	int		output_fd;
	char	*filepath;

	output_fd = 1;
	if (output->fd != NULL)
		output_fd = fd_check(output->fd);
	if (output->file[0] != '/')
		filepath = ft_strjoin("./", output->file);
	else
		filepath = ft_strdup(output->file);
	if (output->type == 3)
		fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		minishell_perror_not_exit(output->file, 1);
	free(filepath);
	dup2(fd, output_fd);
	close(fd);
	if (fd == -1)
		return (0);
	else
		return (1);
}

void	redirect_init(t_process *proc, t_info *info, int i)
{
	if (i != 0)
	{
		dup2(proc[i - 1].fd[0], 0);
		close(proc[i - 1].fd[0]);
	}
	if (i != info->process_num - 1)
	{
		dup2(proc[i].fd[1], 1);
		close(proc[i].fd[1]);
	}
}

int	redirect_process2(t_process *proc, t_info *info, int i)
{
	t_redirect	*redirect;

	redirect = info->commands[i].redirect;
	redirect_init(proc, info, i);
	while (redirect)
	{
		if (redirect->type == 3 || redirect->type == 4)
		{
			if (!redirect_output_file2(redirect))
				return (0);
		}
		else
		{
			if (!redirect_input_file2(redirect))
				return (0);
		}
		redirect = redirect -> next;
	}
	return (1);
}
