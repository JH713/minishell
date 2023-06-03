/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjki2 <hyunjki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:50:09 by hyunjki2          #+#    #+#             */
/*   Updated: 2023/06/03 21:50:44 by hyunjki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	free_command(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		free(command[i++]);
	free(command);
}

void	free_heredocs(t_info *info)
{
	int	i;

	i = 0;
	while (info->heredocs[i])
	{
		free(info->heredocs[i]);
		++i;
	}
	free(info->heredocs);
}

void	free_redirect(t_redirect *rd)
{
	t_redirect	*temp;

	while (rd)
	{
		temp = rd -> next;
		free(rd->fd);
		free(rd->file);
		free(rd);
		rd = temp;
	}
}

void	free_info(t_info *info)
{
	int	i;

	i = 0;
	while (i < info -> process_num)
	{
		free_command((info->commands[i]).command);
		free_redirect((info->commands[i]).input);
		free_redirect((info->commands[i]).output);
		i++;
	}
	free(info->commands);
	free_heredocs(info);
	free(info);
}
