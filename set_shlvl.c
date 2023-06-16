/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:07:55 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/16 14:09:58 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_shlvl(t_env	*lst)
{
	char	*num;
	int		n;

	num = lst->value;
	if (!num && ft_strlen(num) > 4)
		lst->value = ft_strdup("1");
	else if (num[0] == '+' && check_num(&num[1]))
		lst->value = ft_itoa(ft_atoi(num) + 1);
	else if (check_num(num))
	{
		n = ft_atoi(num);
		if (n >= 0 && n < 999)
			lst->value = ft_itoa(n + 1);
		else if (n == 999)
			lst->value = ft_strdup("");
		else
			lst->value = ft_strdup("1");
	}
	else
		lst->value = ft_strdup("1");
	if (num)
		free(num);
}

void	set_shlvl(t_env **env_lst)
{
	t_env	*lst;

	lst = get_lst_by_key(*env_lst, "SHLVL");
	if (lst == NULL)
	{
		lst = env_lst_new("SHLVL=1");
		env_lst_add_back(env_lst, lst);
	}
	else
		update_shlvl(lst);
}
