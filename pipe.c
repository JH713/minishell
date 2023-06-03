/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:00:09 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/03 17:54:42 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe(t_process *process, int process_cnt)
{
	int	i;

	i = 0;
	while (i < process_cnt)
	{
		process[i].n = i;
		if (pipe(process[i].fd) == -1)
			print_error("pipe", 0);
		++i;
	}
	close(process[i - 1].fd[0]);
	close(process[i - 1].fd[1]);
}

void	close_unused_pipes(int i, int process_num, t_process *process)
{
	int	start;
	int	end;

	start = i + 1;
	end = process_num - 2;
	while (start <= end)
	{
		close(process[start].fd[0]);
		close(process[start].fd[1]);
		++start;
	}
	if (i < process_num - 1)
		close(process[i].fd[0]);
}
