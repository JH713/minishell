/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjki2 <hyunjki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:33:32 by hyunjki2          #+#    #+#             */
/*   Updated: 2023/06/01 19:48:07 by hyunjki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	init_command(t_command *command, int num)
{
	command -> input = 0;
	command -> output = 0;

	command->command = (char **)malloc(sizeof(char *) * (num + 1));
	if (!command->command)
		exit(1);
	(command ->command)[num] = 0;
}

int	check_word_num(t_list *list, t_env *env_lst)
{
	t_list	*temp;
	int		len;
	char	*content;
	int		num;
	int		flag;

	flag = 0;
	num = 0;
	temp = list;
	while (temp && !ft_strcmp(temp->content, "|"))
	{
		content = temp -> content;	
		len = ft_strlen(content);
		if ((content[len - 1] == '<' || content[len - 1] == '>'))
			flag = 1;
		else
		{
			if (flag == 0) //환경변수 확장했을 때 수를 더하도록 수정함 
				//여기서 추가로 세주기 
				num += count_word_with_expand(content, env_lst);
			flag = 0;
		}
		temp = temp -> next;
	}
	return (num);
}

t_list	*check_and_init(t_list *list, t_command *command, t_env *env_lst)
{
	int		num;

	if (((char *)list->content)[0] == '|')
		list = list->next;
	num = check_word_num(list, env_lst);
	init_command(command, num);
	return (list);
}

t_list	*put_command(t_info *info, t_command *command, \
			t_list *list, t_env *env_lst)
{
	int		len;
	char	*content;
	int		j;

	list = check_and_init(list, command, env_lst);
	j = 0;
	while (list && !ft_strcmp(list->content, "|"))
	{
		content = list -> content;
		len = ft_strlen(content);
		if (content[len - 1] == '<')
			list = handle_input_redirection(info, list, env_lst, command);
		else if (content[len - 1] == '>')
			list = handle_output_redirection(info, list, env_lst, command);
		else //환경변수 확장한 것 split해서 가져온 후 command에 넣어줌 
			expand_and_fill_command(command, content, env_lst, &j);
		list = list -> next;
	}
	return (list);
}
