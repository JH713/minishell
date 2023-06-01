/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjki2 <hyunjki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:07:01 by hyunjki2          #+#    #+#             */
/*   Updated: 2023/06/01 19:21:09 by hyunjki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	check_type(char	*content)
{
	char	quotes;

	while (*content)
	{
		if (*content == '"' || *content == '\'')
		{	
			quotes = *content;
			content++;
			if (*content && check_if_pair(content, quotes))
				return (2);
		}
		content++;
	}
	return (1);
}

void	check_input(t_info *info, t_list *list, char **fd, int *type)
{
	int		i;
	int		n;
	char	*content;

	content = list->content;
	i = 0;
	n = 0;
	while (ft_isdigit(content[i]))
		i++;
	if (i != 0)
		*fd = ft_substr(content, 0, i);
	else
		*fd = 0;
	while (content[i++] == '<')
		n++;
	if (n == 1)
		*type = 0;
	else
	{
		info->heredoc_num++;
		*type = check_type(list -> next -> content);
	}
}

void	put_input(t_info *info, t_list *list, t_command *command, char *file)
{
	char		*fd;
	int			type;
	t_redirect	*new;

	check_input(info, list, &fd, &type);
	new = malloc_redirect(type, fd, file);
	add_last(&(command -> input), new);
}

t_list	*handle_input_redirection(t_info *info, \
		t_list *list, t_env *env_lst, t_command *command)
{
	char	*file;

	file = check_cmd(list -> next -> content, env_lst);
	put_input(info, list, command, file);
	list = list -> next;
	return (list);
}
