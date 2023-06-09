/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:55:25 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/17 22:46:06 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_input_file(t_redirect *input)
{
	int		fd;
	int		input_fd;
	char	*filepath;

	if (input->fd == NULL)
		input_fd = 0;
	else
		input_fd = fd_check(input->fd);
	if (input->type == 0 || input->type == 1 || input->type == 2)
	{
		if (input->file[0] != '/')
			filepath = ft_strjoin("./", input->file);
		else
			filepath = ft_strdup(input->file);
		fd = open(filepath, O_RDONLY);
		if (fd == -1)
			minishell_perror(input->file, 1);
		free(filepath);
		dup2(fd, input_fd);
		close(fd);
	}
	else
		print_error("input type error", 1);
}

static void	redirect_output_file(t_redirect *output)
{
	int		fd;
	int		output_fd;
	char	*filepath;

	output_fd = 1;
	if (output->fd != NULL)
		output_fd = fd_check(output->fd);
	if (output->type == 3 || output->type == 4)
	{
		if (output->file[0] != '/')
			filepath = ft_strjoin("./", output->file);
		else
			filepath = ft_strdup(output->file);
		if (output->type == 3)
			fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			minishell_perror(output->file, 1);
		free(filepath);
		dup2(fd, output_fd);
		close(fd);
	}
	else
		print_error("input type error", 1);
}

void	redirect_process(t_process *proc, t_info *info, int i)
{
	t_redirect	*redirect;

	redirect = info->commands[i].redirect;
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
	while (redirect)
	{
		if (redirect->type == 3 || redirect->type == 4)
			redirect_output_file(redirect);
		else
			redirect_input_file(redirect);
		redirect = redirect -> next;
	}
}
