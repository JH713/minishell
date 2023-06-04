/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:54:39 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/04 19:42:51 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	exit_status;

static char	*get_temp_name(void)
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

static void	hd_sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(2);
}

static int	hd_input(t_redirect *input, t_info *info, int j)
{
	char		*tempfile;
	int			fd;
	char		*line;
	pid_t		pid;

	tempfile = get_temp_name();
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, hd_sigint_handler);
		fd = open(tempfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			exit(1);
		line = readline("> ");
		if (line == NULL)
			exit(0);
		while (ft_strncmp(input->file, line, ft_strlen(input->file) + 1) != 0)
		{
			ft_putendl_fd(line, fd);
			free(line);
			line = readline("> ");
			if (line == NULL)
				exit(0);
		}
		exit(0);
	}
	int status;
	int	stat;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		stat = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		stat = WTERMSIG(status);
	else
		stat = 0;
	signal(SIGINT, sigint_handler);
	free(input->file);
	input->file = tempfile;
	info->heredocs[j] = ft_strdup(input->file);
	if (stat == 2)
	{
		exit_status = 1;
		return (0);
	}
	return (1);
}

static int	hd_input_expand(t_redirect *input, t_env *env, t_info *info, int j)
{
	char		*tempfile;
	int			fd;
	char		*line;
	pid_t		pid;

	tempfile = get_temp_name();
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, hd_sigint_handler);
		fd = open(tempfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			exit(1);
		line = readline("> ");
		if (line == NULL)
			exit(0);
		while (ft_strncmp(input->file, line, ft_strlen(input->file) + 1) != 0)
		{
			expand_env(&line, env);
			ft_putendl_fd(line, fd);
			free(line);
			line = readline("> ");
			if (line == NULL)
				exit(0);
		}
		exit(0);
	}
	int status;
	int	stat;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		stat = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		stat = WTERMSIG(status);
	else
		stat = 0;
	signal(SIGINT, sigint_handler);
	free(input->file);
	input->file = tempfile;
	info->heredocs[j] = ft_strdup(input->file);
	if (stat == 2)
	{
		exit_status = 1;
		return (0);
	}
	else if (stat == 1)
		exit(1);
	
	return (1);
}

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

int	create_heredoc_temp(t_info *info, t_env *env_lst)
{
	int			i;
	int			j;
	t_redirect	*input;
	int			ret;

	i = 0;
	j = 0;
	malloc_heredocs(info);
	while (i < info->process_num)
	{
		input = info->commands[i].input;
		while (input)
		{
			if (input->type == 1)
				ret = hd_input_expand(input, env_lst, info, j);
			if (input->type == 2)
				ret = hd_input(input, info, j);
			if (ret == 0)
				return (unlink_heredocs(info));
			input = input->next;
			j++;
		}
		++i;
	}
	return (1);
}
