/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_fill_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjki2 <hyunjki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:31:12 by hyunjki2          #+#    #+#             */
/*   Updated: 2023/06/01 19:20:25 by hyunjki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"minishell.h"

size_t	get_word_len(char *str, size_t len, size_t temp)
{
	while (str[len])
	{
		if (str[len] == '"')
		{
			temp = len;
			++len;
			while (str[len] && str[len] != '"')
				++len;
			if (str[len] == 0)
				len = temp;
		}
		else if (str[len] == '\'')
		{
			temp = len;
			++len;
			while (str[len] && str[len] != '\'')
				++len;
			if (str[len] == 0)
				len = temp;
		}
		else if (str[len] == ' ')
			break ;
		++len;
	}
	return (len);
}

char	**split_word(char *str, int num)
{
	char	**str_arr;
	size_t	i;
	size_t	j;
	size_t	word_len;

	if (str == NULL)
		return (NULL);
	str_arr = (char **)malloc(sizeof(char *) * (num + 1));
	i = 0;
	j = 0;
	while (i < (size_t)num)
	{
		while (str[j] == ' ')
			j++;
		word_len = get_word_len(&str[j], 0, 0);
		str_arr[i] = ft_substr(str, j, word_len);
		j += word_len;
		++i;
	}
	str_arr[i] = 0;
	return (str_arr);
}

void	expand_and_fill_command(t_command *command, \
		char *content, t_env *env_lst, int *j)
{
	char	*temp;
	int		temp_num;
	char	**temp_arr;
	int		i;

	temp_num = count_word_with_expand(content, env_lst);
	temp = content;
	expand_env_2(&temp, env_lst);
	temp_arr = split_word(temp, temp_num);
	free(temp);
	i = 0;
	while (temp_arr[i])
	{
		(command->command)[(*j)++] = ft_strdup(check_cmd(temp_arr[i], env_lst));
		++i;
	}
	free(temp_arr);
}
