/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_in_parsing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:13:36 by hyunjki2          #+#    #+#             */
/*   Updated: 2023/06/17 15:53:13 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	join_env_2(char **line, char *env_value, int start, int end)
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

int	plus_i(int *i)
{
	++*i;
	return (0);
}

int	expand_env_inner(char **line, t_env *env_lst, int *i, int flag)
{
	char	*env_value;
	int		j;
	int		len;

	len = 0;
	if ((*line)[*i] == '$' && (*line)[*i + 1] == '?')
	{
		handle_exit_status_variable(line, i, &env_value);
		len = 1;
	}
	else if ((*line)[*i] == '$')
	{
		handle_variable_expansion(line, flag, i, &j);
		if (j == 1)
			return (plus_i(i));
		len = get_environment_variable_value(&(*line)[*i + 1], \
				env_lst, &env_value, j);
		join_env_2(line, env_value, *i, *i + j);
		*i += ft_strlen(env_value);
	}
	else
		return (plus_i(i));
	return (ft_strlen(env_value) - (len + 1));
}

void	check_quotes_env(char **line, t_env *env_lst, int *i)
{
	int		end;
	int		ret;

	if ((*line)[*i] == '"')
	{
		ret = check_end(*line, *i, '"');
		end = *i + ret;
		if (ret == 0)
		{
			while (*i <= end)
				end += expand_env_inner(line, env_lst, i, 0);
		}
		else
		{
			while (*i <= end)
				end += expand_env_inner(line, env_lst, i, 0);
		}
	}
	else if ((*line)[*i] == '\'')
		*i = *i + check_end(*line, *i, '\'') + 1;
	else
		expand_env_inner(line, env_lst, i, 0);
}

void	expand_env_2(char **line, t_env *env_lst)
{
	int		i;

	i = 0;
	if (*line == NULL)
		return ;
	while ((*line)[i])
		check_quotes_env(line, env_lst, &i);
}
