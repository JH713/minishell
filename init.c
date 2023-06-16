/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 05:38:27 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/16 14:27:32 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init(int argc, char *argv[], char **env, char **command)
{
	t_env	*env_lst;

	(void)argv;
	if (argc != 1)
	{
		ft_putendl_fd("Error: No arguments should be provided.", 2);
		exit(1);
	}
	env_lst = NULL;
	get_env_lst(&env_lst, env);
	*command = NULL;
	print_maenggu();
	return (env_lst);
}

void	init_in_while(char *command)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	if (command)
		free(command);
}
