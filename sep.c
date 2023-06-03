/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:40:55 by hyunjki2          #+#    #+#             */
/*   Updated: 2023/06/03 23:00:19 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	is_not_sep(char c)
{
	if (c == ' ' || c == '<' || c == '>' || c == '|')
		return (0);
	return (1);
}

int	check_sep_input(char *sep, int i)
{
	char *temp;
	while (sep[i] == '<' && i < 2)
		++i;
	if (sep[i + 1] == 0)
	{
		temp = ft_substr(&sep[i], 0, 1);
		error_m1(temp);
		free(temp);
	}
	else
	{
		temp = ft_substr(&sep[i], 0, 2);
		error_m1(temp);
		free(temp);
	}
	return (0);
}

int	check_sep_output(char *sep, int i)
{
	char *temp;

	while (sep[i] == '>' && i < 2)
		++i;
	if (sep[i + 1] == 0)
	{
		temp = ft_substr(&sep[i], 0, 1);
		error_m1(temp);
		free(temp);
	}
	else
	{
		temp = ft_substr(&sep[i], 0, 2);
		error_m1(temp);
		free(temp);
	}
	return (0);
}

int	check_sep(char *sep)
{
	int	i;

	i = 1;
	if (sep[0] == '<')
	{
		if (!(ft_strcmp(sep, "<") || ft_strcmp(sep, "<<")))
			return (check_sep_input(sep, i));
	}
	else if (sep[0] == '>')
	{
		if (!(ft_strcmp(sep, ">") || ft_strcmp(sep, ">>")))
			return (check_sep_output(sep, i));
	}
	return (1);
}
