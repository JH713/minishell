/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_word_with_expand.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:33:46 by hyunjki2          #+#    #+#             */
/*   Updated: 2023/06/05 04:39:06 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	count_if_quotes(char **temp, int *i)
{
	int	j;

	if ((*temp)[*i] == '"')
	{
		j = *i;
		++(*i);
		while ((*temp)[*i] && (*temp)[*i] != '"')
			++(*i);
		if ((*temp)[*i] == 0)
			*i = j;
	}
	else if ((*temp)[*i] == '\'')
	{
		j = *i;
		++(*i);
		while ((*temp)[*i] && (*temp)[*i] != '\'')
			++(*i);
		if ((*temp)[*i] == 0)
			*i = j;
	}
}

int	count_words(char *temp, int i)
{
	int		cnt;

	cnt = 1;
	while (temp[i] == ' ')
		++i;
	while (temp[i])
	{
		if (temp[i] == '"' || temp[i] == '\'')
			count_if_quotes(&temp, &i);
		else if (temp[i] == ' ')
		{
			++cnt;
			while (temp[i] == ' ')
				++i;
			continue ;
		}
		++i;
	}
	free(temp);
	return (cnt);
}

int	count_word_with_expand(char *content, t_env *env_lst)
{
	int		j;
	char	*temp;

	if (content == NULL || content[0] == 0)
		return (0);
	temp = ft_strdup(content);
	expand_env_2(&temp, env_lst);
	j = ft_strlen(temp) - 1;
	while (j >= 0 && temp[j] == ' ')
		--j;
	if (j < 0)
	{
		free(temp);
		return (0);
	}
	else
		temp[j + 1] = 0;
	return (count_words(temp, 0));
}
