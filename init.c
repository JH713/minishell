/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 05:38:27 by jihyeole          #+#    #+#             */
/*   Updated: 2023/05/30 20:45:01 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int exit_status;

void	init(int argc, char *argv[], char **env, t_env **env_lst)
{
	(void)argv;
	if (argc != 1)
	{
		ft_putendl_fd("Error: No arguments should be provided.", 2);
		exit(1);
	}
	*env_lst = NULL;
	get_env_lst(env_lst, env);
}
