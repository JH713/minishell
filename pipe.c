/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:00:09 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/17 23:46:23 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe(t_process *process, t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->process_num)
	{
		process[i].n = i;
		if (pipe(process[i].fd) == -1)
		{
			print_error_not_exit("pipe", 0);
			j = 0;
			while (j < i)
			{
				close(process[j].fd[0]);
				close(process[j].fd[1]);
				++j;
			}
			cleanup_memory(info, process);
			return (0);
		}
		++i;
	}
	close(process[i - 1].fd[0]);
	close(process[i - 1].fd[1]);
	return (1);
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
