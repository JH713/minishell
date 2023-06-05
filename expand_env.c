/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:23:07 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/05 17:19:38 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_env(char **line, char *env_value, int start, int end)
{
	char	*temp;
	char	*head;
	char	*tail;

	temp = *line;
	if (start == 0)
		head = ft_strdup("");
	else
		head = ft_substr(temp, 0, start);
	if (end == (int)ft_strlen(temp))
		tail = ft_strdup("");
	else
		tail = ft_substr(temp, end, ft_strlen(temp) - end);
	free(temp);
	temp = ft_strjoin(head, env_value);
	free(head);
	*line = ft_strjoin(temp, tail);
	free(tail);
	free(temp);
}

void	expand_by_join(char **line, t_env *env_lst, int *i)
{
	char	*env_key;
	char	*env_value;
	t_env	*lst;
	int		j;

	j = 1;
	while ((*line)[(*i) + j] && ft_inset((*line)[(*i) + j], "\"\' $") == 0)
		j++;
	if (j == 1)
	{
		++(*i);
		return ;
	}
	env_key = ft_substr(&(*line)[(*i) + 1], 0, j - 1);
	lst = get_lst_by_key(env_lst, env_key);
	free(env_key);
	if (lst == NULL)
		env_value = "";
	else
		env_value = lst->value;
	join_env(line, env_value, (*i), (*i) + j);
	(*i) += ft_strlen(env_value);
}

void	expand_env(char **line, t_env *env_lst)
{
	int		i;
	char	*env_value;

	i = 0;
	if (*line == NULL)
		return ;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && (*line)[i + 1] == '?')
		{
			env_value = ft_itoa(g_exit_status);
			join_env(line, env_value, i, i + 2);
			i += ft_strlen(env_value);
			free(env_value);
		}
		else if ((*line)[i] == '$')
			expand_by_join(line, env_lst, &i);
		else
			++i;
	}
}
