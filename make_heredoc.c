/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:54:39 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/05 16:56:06 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	malloc_heredocs(t_info *info)
{
	int	i;

	i = 0;
	info->heredocs = (char **)malloc(sizeof(char *) * (info->heredoc_num + 1));
	while (i <= info->heredoc_num)
	{
		info->heredocs[i] = NULL;
		++i;
	}
}

static void	hd_child_proc(char *tmp, t_redirect *input, t_info *info, int type)
{
	int			fd;
	char		*line;

	signal(SIGINT, hd_sigint_handler);
	fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		exit(1);
	line = readline("> ");
	if (line == NULL)
		exit(0);
	while (ft_strncmp(input->file, line, ft_strlen(input->file) + 1) != 0)
	{
		if (type == 1)
			expand_env(&line, info->env);
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("> ");
		if (line == NULL)
			exit(0);
	}
	exit(0);
}

static int	heredoc_input(t_redirect *input, t_info *info, int type, int j)
{
	char		*tempfile;
	pid_t		pid;
	int			status;
	int			stat;

	tempfile = get_temp_name();
	pid = fork();
	if (pid == 0)
		hd_child_proc(tempfile, input, info, type);
	waitpid(pid, &status, 0);
	stat = 0;
	if (WIFEXITED(status))
		stat = WEXITSTATUS(status);
	free(input->file);
	input->file = tempfile;
	info->heredocs[j] = ft_strdup(input->file);
	if (stat == 2)
	{
		g_exit_status = 1;
		unlink_heredocs(info);
		return (0);
	}
	else if (stat == 1)
		exit(1);
	return (1);
}

static int	process_heredoc_inputs(t_redirect *input, t_info *info)
{
	int	j;
	int	ret;

	j = 0;
	while (input)
	{
		if (input->type == 0)
		{
			input = input->next;
			continue ;
		}
		ret = heredoc_input(input, info, input->type, j);
		if (ret == 0)
			return (unlink_heredocs(info));
		input = input->next;
		j++;
	}
	return (1);
}

int	create_heredoc_temp(t_info *info)
{
	int			i;
	t_redirect	*input;

	i = 0;
	malloc_heredocs(info);
	signal(SIGINT, SIG_IGN);
	while (i < info->process_num)
	{
		input = info->commands[i].input;
		if (process_heredoc_inputs(input, info) == 0)
		{
			free_info(info);
			return (0);
		}
		++i;
	}
	signal(SIGINT, sigint_handler);
	return (1);
}
