/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_in_parsing2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjki2 <hyunjki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:21:49 by hyunjki2          #+#    #+#             */
/*   Updated: 2023/06/01 19:20:54 by hyunjki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"minishell.h"

void	get_environment_variable_value(char *line, \
		t_env *env_lst, char **env_value, int j)
{
	t_env	*lst;
	char	*env_key;

	env_key = ft_substr(line, 0, j - 1);
	lst = get_lst_by_key(env_lst, env_key);
	if (lst == NULL)
		*env_value = "";
	else
		*env_value = lst->value;
}

int	check_prev_quotes(char *line, int i)
{
	while (line[i] != '"')
	{
		if (line[i] == '\'')
			return (1);
		i--;
	}
	return (0);
}

void	handle_variable_expansion(char **line, int flag, int *i, int *j)
{
	*j = 1;
	if (flag == 1)
	{
		while ((*line)[*i + *j] && ft_inset((*line)[*i + *j], "\" $") == 0)
		{
			if ((*line)[*i + *j] == '\'')
			{
				if (check_prev_quotes((*line), *i + *j))
					break ;
			}
			else
				*j += 1;
		}
	}
	else
	{
		while ((*line)[*i + *j] && ft_inset((*line)[*i + *j], "\"\' $") == 0)
			*j += 1;
	}
}

void	handle_exit_status_variable(char **line, int *i, char **env_value)
{
	*env_value = ft_itoa(exit_status);
	join_env_2(line, *env_value, *i, *i + 2);
	*i += ft_strlen(*env_value);
}
