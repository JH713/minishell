/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:36:38 by hyunjki2          #+#    #+#             */
/*   Updated: 2023/06/05 15:47:18 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotes_in_cmd(char *content, char **temp, int *i, int *j)
{
	char	quotes;

	quotes = content[*i];
	if (check_if_pair(content + *i + 1, quotes))
	{
		(*i)++;
		while (1)
		{
			if (content[*i] == quotes)
			{
				(*i)++;
				break ;
			}
			(*temp)[(*j)++] = content[(*i)++];
		}
	}
	else
	{
		(*temp)[(*j)++] = content[(*i)++];
	}
}

char	*check_cmd(char	*content)
{
	char	*temp;
	int		i;
	int		j;

	temp = (char *)malloc(sizeof(char) * (ft_strlen(content)+1));
	if (!temp)
		exit(1);
	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] == '"' || content[i] == '\'')
			check_quotes_in_cmd(content, &temp, &i, &j);
		else
			temp[j++] = content[i++];
	}
	temp[j] = 0;
	return (temp);
}
