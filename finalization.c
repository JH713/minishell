/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:03:24 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/10 01:32:57 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unlink_heredocs(t_info *comm_info)
{
	int	i;

	i = 0;
	while (comm_info->heredocs[i])
	{
		unlink(comm_info->heredocs[i]);
		++i;
	}
	return (0);
}

void	wait_all_child(t_info *info, t_process *process)
{
	int	i;
	int	status;

	i = 0;
	while (i < info->process_num)
	{
		waitpid(process[i].pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_exit_status = WTERMSIG(status);
		++i;
	}
	cleanup_memory(info, process);
}
