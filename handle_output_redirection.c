/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_output_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:09:08 by hyunjki2          #+#    #+#             */
/*   Updated: 2023/06/15 19:19:34 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	put_output(t_info *info, char *content, t_command *command, char *file)
{
	int			i;
	char		*fd;
	int			n;
	int			type;
	t_redirect	*new;

	i = 0;
	n = 0;
	while (ft_isdigit(content[i]))
		i++;
	if (i != 0)
		fd = ft_substr(content, 0, i);
	else
		fd = 0;
	while (content[i++] == '>')
		n++;
	if (n == 1)
		type = 0;
	else
	{
		info->heredoc_num++;
		type = 1;
	}
	new = malloc_redirect(type, fd, file);
	add_last(&(command -> output), new);
}

t_list	*handle_output_redirection(t_info *info, t_list *list, \
		t_env *env_lst, t_command *command)
{
	char	*file;
	char	*content;

	content = list -> content;
	list = list -> next;
	file = check_cmd2(list -> content, env_lst);
	put_output(info, content, command, file);
	return (list);
}

static void	put_output2(t_info *info, char *content, t_command *command, char *file)
{
	int			i;
	char		*fd;
	int			n;
	int			type;
	t_redirect	*new;

	i = 0;
	n = 0;
	while (ft_isdigit(content[i]))
		i++;
	if (i != 0)
		fd = ft_substr(content, 0, i);
	else
		fd = 0;
	while (content[i++] == '>')
		n++;
	if (n == 1)
		type = 3;
	else
	{
		info->heredoc_num++;
		type = 4;
	}
	new = malloc_redirect(type, fd, file);
	add_last(&(command -> redirect), new);
}

t_list	*handle_output_redirection2(t_info *info, t_list *list, \
		t_env *env_lst, t_command *command)
{
	char	*file;
	char	*content;

	content = list -> content;
	list = list -> next;
	file = check_cmd2(list -> content, env_lst);
	put_output2(info, content, command, file);
	return (list);
}
