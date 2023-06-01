/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjki2 <hyunjki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:33:01 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/01 21:14:15 by hyunjki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//int	exit_status;

// void	add_list(char *str, t_list **cmds)
// {
// 	t_list	*new;

// 	new = ft_lstnew(str);
// 	ft_lstadd_back(cmds, new);
// }

// int	is_not_sep(char c)
// {
// 	if (c == ' ' || c == '<' || c == '>' || c == '|')
// 		return (0);
// 	return (1);
// }

// int	ft_strcmp(char	*s1, char *s2)
// {
// 	while (*s1 || *s2)
// 	{
// 		if (*s1 != *s2)
// 			return (0);
// 		s1++;
// 		s2++;
// 	}
// 	return (1);
// }

// int	check_end(char *command, int i, char c)
// {
// 	int	len;

// 	len = 1;
// 	i++;
// 	while (command[i])
// 	{
// 		if (command[i++] == c)
// 			return (len);
// 		len++;
// 	}
// 	return (0);
// }

// int	check_prev(char *command, int i, t_list *cmds)
// {
// 	t_list	*temp;
// 	char	*c;
// 	int		k;

// 	k = 0;
// 	if (i - 1 >= 0 && ft_isdigit(command[i - 1]))
// 	{
// 		temp = ft_lstlast(cmds);
// 		c = temp -> content;
// 		while (c[k])
// 		{
// 			if (!ft_isdigit(c[k]))
// 				return (0);
// 			k++;
// 		}
// 		return (1);
// 	}
// 	return (0);
// }

// int check_sep_input(char *sep, int i)
// {
// 	while (sep[i] == '<' && i < 2)
// 		++i;
// 	if (sep[i + 1] == 0)
// 		error_m1(ft_substr(&sep[i], 0, 1));
// 	else
// 		error_m1(ft_substr(&sep[i], 0, 2));
// 	return (0);
// }

// int check_sep_output(char *sep, int i)
// {
// 	while (sep[i] == '>' && i < 2)
// 		++i;
// 	if (sep[i + 1] == 0)
// 		error_m1(ft_substr(&sep[i], 0, 1));
// 	else
// 		error_m1(ft_substr(&sep[i], 0, 2));
// 	return (0);
// }

// int	check_sep(char *sep)
// {
// 	int	i;

// 	i = 1;
// 	if (sep[0] == '<')
// 	{
// 		if (!(ft_strcmp(sep, "<") || ft_strcmp(sep, "<<")))
// 			return (check_sep_input(sep, i));
// 	}
// 	else if (sep[0] == '>')
// 	{
// 		if (!(ft_strcmp(sep, ">") || ft_strcmp(sep, ">>")))
// 			return (check_sep_output(sep, i));
// 	}
// 	return (1);
// }

// int	find_sep(char *command, int start, int i, t_list **cmds)
// {
// 	char	*sep;
// 	t_list	*last;

// 	if (check_prev(command, i, *cmds))
// 	{
// 		while (command[i] && (command[i] == '<' || command[i] == '>'))
// 			i++;
// 		last = ft_lstlast(*cmds);//전꺼 free?
// 		sep = ft_substr(command, start, i - start);
// 		if (!check_sep(sep))
// 			return (-1);
// 		last -> content = ft_strjoin(last -> content, sep);
// 	}
// 	else
// 	{
// 		while (command[i] && (command[i] == '<' || command[i] == '>'))
// 				i++;
// 		sep = ft_substr(command, start, i - start);
// 		if (!check_sep(sep))
// 			return (-1);
// 		add_list(sep, cmds);
// 	}
// 	return (i - start);
// }

// int	get_word(char *command, int i, t_list **cmds, int *flag)
// {
// 	int	start;

// 	start = i;
// 	while (command[i] && is_not_sep(command[i]))
// 	{
// 		if (command[i] == '"' || command[i] == '\'')
// 			i = i + check_end(command, i, command[i]);
// 		i++;
// 	}
// 	add_list(ft_substr(command, start, i - start), cmds);
// 	*flag = 0;
// 	return (i);
// }

// int handle_consecutive_redirection_error(char *command, int i)
// {
// 	if (!command[i + 1] || command[i + 1] != command[i])
// 		error_m1(ft_substr(&command[i], 0, 1));
// 	else
// 		error_m1(ft_substr(&command[i], 0, 2));
// 	return (-1);
// }

// int	get_operator(char *command, int i, t_list **cmds, int *flag)
// {
// 	int	start;
// 	int	ret;

// 	if (command[i] && (command[i] == '<' || command[i] == '>'))
// 	{
// 		start = i;
// 		if (*flag == 1)
// 			return (handle_consecutive_redirection_error(command, i));
// 		ret = find_sep(command, start, i, cmds);
// 		if (ret == -1)
// 			return (-1);
// 		i += ret;
// 		*flag = 1;
// 	}
// 	if (command[i] == '|')
// 	{
// 		if (*flag == 2 || *flag == 1)
// 		{
// 			error_m(0);
// 			return (-1);
// 		}
// 		add_list(ft_substr(command, i++, 1), cmds);
// 		*flag = 2;
// 	}
// 	return (i);
// }


// t_list	*split_command(char *command)
// {
// 	t_list	*cmds;
// 	int		i;
// 	int		flag;

// 	cmds = 0;
// 	i = 0;
// 	flag = 0;
// 	while (command[i])
// 	{
// 		if (is_not_sep(command[i]))
// 			i = get_word(command, i, &cmds, &flag);
// 		else
// 		{
// 			while (command[i] && command[i] == ' ')
// 				i++;
// 			if (command[i] && (command[i] == '<' || command[i] == '>' \
// 					|| command[i] == '|'))
// 			{
// 				i = get_operator(command, i, &cmds, &flag);
// 				if (i == -1)
// 					return (NULL); // list free하기? 
// 			}
// 		}
// 	}
// 	return (cmds);
// }

// int	check_error(t_list *list)
// {
// 	int		flag;
// 	char	*c;

// 	flag = 0;
// 	c = list -> content;
// 	if (ft_strcmp(c, "|"))
// 	{
// 		error_m(0);
// 		return (1);
// 	}
// 	c = ft_lstlast(list)->content;
// 	if (ft_strcmp(c, "<") || ft_strcmp(c, ">") || \
// 				ft_strcmp(c, "<<") || ft_strcmp(c, ">>"))
// 	{
// 		error_m(6);
// 		return (1);
// 	}
// 	return (0);
// }
///////////////////////////////////////////////////////////////
// int	pipe_num(t_list	*list)
// {
// 	t_list	*temp;
// 	int		num;

// 	temp = list;
// 	num = 0;
// 	while (temp)
// 	{
// 		if (ft_strcmp(temp->content, "|"))
// 			num++;
// 		temp = temp -> next;
// 	}
// 	return (num);
// }

// void	add_last(t_redirect **rd, t_redirect * new)
// {
// 	t_redirect	*temp;

// 	if (new == NULL)
// 		return ;
// 	if (*rd == NULL)
// 		*rd = new;
// 	else
// 	{
// 		temp = *rd;
// 		while (temp->next != NULL)
// 			temp = temp->next;
// 		temp->next = new;
// 	}
// }

// int	check_if_pair(char	*content, char quotes)
// {
// 	while (*content)
// 	{
// 		if (*content == quotes)
// 			return (1);
// 		content++;
// 	}
// 	return (0);
// }

// t_redirect	*malloc_redirect(int type, char *fd, char *file)
// {
// 	t_redirect *new;

// 	new = malloc(sizeof(t_redirect));
// 	if (!new)
// 		exit(1);
// 	new -> type = type;
// 	new -> fd = fd;
// 	new -> file = file;
// 	new -> next = 0;
// 	return (new);
// }

// int	check_type(char	*content)
// {
// 	char	quotes;

// 	while (*content)
// 	{
// 		if (*content == '"' || *content == '\'')
// 		{	
// 			quotes = *content;
// 			content++;
// 			if (*content && check_if_pair(content, quotes))
// 				return (2);
// 		}
// 		content++;
// 	}
// 	return (1);
// }

// void	check_input(t_info *info, t_list *list, char **fd, int *type)
// {
// 	int		i;
// 	int		n;
// 	char	*content;

// 	content = list->content;
// 	i = 0;
// 	n = 0;
// 	while (ft_isdigit(content[i]))
// 		i++;
// 	if (i != 0)
// 		*fd = ft_substr(content, 0, i);
// 	else
// 		*fd = 0;
// 	while (content[i++] == '<')
// 		n++;
// 	if (n == 1)
// 		*type = 0;
// 	else
// 	{
// 		info->heredoc_num++;
// 		*type = check_type(list -> next -> content);
// 	}
// }


// void	put_input(t_info *info, t_list *list, t_command *command, char *file)
// {
// 	// int			i;
// 	char		*fd;
// 	// int			n;
// 	int			type;
// 	t_redirect	*new;

// 	check_input(info, list, &fd, &type);
// 	new = malloc_redirect(type, fd, file);
// 	add_last(&(command -> input), new);
// }

// void	put_output(t_info *info, char *content, t_command *command,char *file)
// {
// 	int			i;
// 	char		*fd;
// 	int			n;
// 	int			type;
// 	t_redirect	*new;

// 	i = 0;
// 	n = 0;
// 	while (ft_isdigit(content[i]))
// 		i++;
// 	if (i != 0)
// 		fd = ft_substr(content, 0, i);
// 	else
// 		fd = 0;
// 	while (content[i++] == '>')
// 		n++;
// 	if (n == 1)
// 		type = 0;
// 	else
// 	{
// 		info->heredoc_num++;
// 		type = 1;
// 	}
// 	new = malloc_redirect(type, fd, file);
// 	add_last(&(command -> output), new);
// }

// void	init_command(t_command *command, int num)
// {
// 	command -> input = 0;
// 	command -> output = 0;

// 	command->command = (char **)malloc(sizeof(char *) * (num + 1));
// 	if (!command->command)
// 		exit(1);
// 	(command ->command)[num] = 0;
// }

// void	join_env_2(char **line, char *env_value, int start, int end)
// {
// 	char	*temp;
// 	char	*head;
// 	char	*tail;

// 	temp = *line;
// 	if (start == 0)
// 		head = NULL;
// 	else
// 		head = ft_substr(temp, 0, start);
// 	if (end == (int)ft_strlen(temp))
// 		tail = NULL;
// 	else
// 		tail = ft_substr(temp, end, ft_strlen(temp) - end);
// 	free(temp);
// 	temp = ft_strjoin(head, env_value);
// 	*line = ft_strjoin(temp, tail);
// 	free(temp);
// }

// int	check_prev_quotes(char *line, int i)
// {
// 	while (line[i] != '"')
// 	{
// 		if (line[i] == '\'')
// 			return (1);
// 		i--;
// 	}
// 	return (0);
// }

// void handle_variable_expansion(char **line, int flag, int *i, int *j)
// {
// 	*j = 1;
// 	if (flag == 1)
// 	{
// 		while ((*line)[*i + *j] && ft_inset((*line)[*i + *j], "\" $") == 0)
// 		{
// 			if ((*line)[*i + *j] == '\'')
// 			{
// 				if (check_prev_quotes((*line), *i + *j))
// 					break ;
// 			}
// 			else
// 				*j += 1;
// 		}
// 	}
// 	else
// 	{
// 		while ((*line)[*i + *j] && ft_inset((*line)[*i + *j], "\"\' $") == 0)
// 			*j += 1;
// 	}
// }

// void handle_exit_status_variable(char **line, int *i, char **env_value)
// {
// 	*env_value = ft_itoa(exit_status);
// 	join_env_2(line, *env_value, *i, *i + 2);
// 	*i += ft_strlen(*env_value);
// }

// void	get_environment_variable_value(char *line, t_env *env_lst, char **env_value, int j)
// {
// 	t_env	*lst;
// 	char	*env_key;

// 	env_key = ft_substr(line, 0, j - 1);
// 	lst = get_lst_by_key(env_lst, env_key);
// 	if (lst == NULL)
// 		*env_value = "";
// 	else
// 		*env_value = lst->value;
// }

// int	expand_env_inner(char **line, t_env *env_lst, int *i, int flag)
// {
// 	char	*env_value;
// 	int		j;

// 	if ((*line)[*i] == '$' && (*line)[*i + 1] == '?')
// 		handle_exit_status_variable(line, i, &env_value);
// 	else if ((*line)[*i] == '$')
// 	{
// 		handle_variable_expansion(line, flag, i, &j);
// 		if (j == 1)
// 		{
// 			++*i;
// 			return (0);
// 		}
// 		get_environment_variable_value(&(*line)[*i + 1], env_lst, &env_value, j);
// 		join_env_2(line, env_value, *i, *i + j);
// 		*i += ft_strlen(env_value);
// 	}
// 	else
// 	{
// 		++*i;
// 		return (0);
// 	}
// 	return (ft_strlen(env_value));
// }

// void	check_quotes_env(char **line, t_env *env_lst, int *i)
// {
// 	int		end;
// 	int		ret;

// 	if ((*line)[*i] == '"')
// 	{
// 		ret = check_end(*line, *i, '"');
// 		end = *i + ret;
// 		if (ret == 0)
// 		{
// 			while (*i <= end)
// 			end += expand_env_inner(line, env_lst, i, 0);
// 		}
// 		else
// 		{
// 			while (*i <= end)
// 				end += expand_env_inner(line, env_lst, i, 1);
// 		}
// 	}
// 	else if ((*line)[*i] == '\'')
// 		*i = *i + check_end(*line, *i, '\'') + 1;
// 	else
// 		expand_env_inner(line, env_lst, i, 0);
// }


// void	expand_env_2(char **line, t_env *env_lst)
// {
// 	int		i;
// 	// int		end;
// 	// int		ret;

// 	i = 0;
// 	if (*line == NULL)
// 		return ;
// 	while ((*line)[i])
// 		check_quotes_env(line, env_lst, &i);
// }

// void	check_quotes_in_cmd(char *content, char **temp, int *i, int *j)
// {
// 	char	quotes;

// 	quotes = content[*i];
// 	if (check_if_pair(content + *i, quotes))
// 	{
// 		(*i)++;
// 		while (1)
// 		{
// 			if (content[*i] == quotes)
// 			{
// 				(*i)++;
// 				break ;
// 			}
// 			(*temp)[(*j)++] = content[(*i)++];
// 		}
// 	}
// 	else
// 		(*temp)[(*j)++] = content[(*i)++];
// }

// char	*check_cmd(char	*content, t_env *env_lst)
// {
// 	char	*temp;
// 	int		i;
// 	int		j;

// 	if (ft_strchr(content, '$'))
// 		expand_env_2(&content, env_lst);
// 	temp = (char *)malloc(sizeof(char) * (ft_strlen(content)+1));
// 	if (!temp)
// 		exit(1);
// 	i = 0;
// 	j = 0;
// 	while (content[i])
// 	{
// 		if (content[i] == '"' || content[i] == '\'')
// 			check_quotes_in_cmd(content, &temp, &i, &j);
// 		else
// 			temp[j++] = content[i++];
// 	}
// 	temp[j] = 0;
// 	return (temp);
// }

// void	count_if_quotes(char **temp, int *i)
// {
// 	int	j;

// 	if ((*temp)[*i] == '"')
// 	{
// 		j = *i;
// 		++(*i);
// 		while ((*temp)[*i] && (*temp)[*i] != '"')
// 			++(*i);
// 		if ((*temp)[*i] == 0)
// 			*i = j;
// 	}
// 	else if ((*temp)[*i] == '\'')
// 	{
// 		j = *i;
// 		++(*i);
// 		while ((*temp)[*i] && (*temp)[*i] != '\'')
// 			++(*i);
// 		if ((*temp)[*i] == 0)
// 			*i = j;
// 	}
// }


// int	count_words(char *temp, int i)
// {
// 	int		cnt;

// 	cnt = 1;
// 	while (temp[i] == ' ')
// 		++i;
// 	while (temp[i])
// 	{
// 		if (temp[i] == '"' || temp[i] == '\'')
// 			count_if_quotes(&temp, &i);
// 		else if (temp[i] == ' ')
// 		{
// 			++cnt;
// 			while (temp[i] == ' ')
// 				++i;
// 			continue ;
// 		}
// 		++i;
// 	}
// 	free(temp);
// 	return (cnt);
// }

// int count_word_with_expand(char *content, t_env *env_lst)
// {
// 	//int		i;
// 	//int		cnt;
// 	int		j;
// 	// char	*env_key;
// 	// char	*env_value;
// 	// t_env	*lst;
// 	char	*temp;

// 	if (content == NULL || content[0] == 0)
// 		return (0);
// 	temp = ft_strdup(content);
// 	expand_env_2(&temp, env_lst);
// 	j = ft_strlen(temp) - 1;
// 	while (j >= 0 && temp[j] == ' ')
// 		--j;
// 	if (j < 0)
// 	{
// 		free(temp);
// 		return (0);
// 	}
// 	else
// 		temp[j + 1] = 0;
// 	return (count_words(temp, 0));
// }

// int	check_word_num(t_list *list, t_env *env_lst)
// {
// 	t_list	*temp;
// 	int		len;
// 	char	*content;
// 	int		num;
// 	int		flag;

// 	flag = 0;
// 	num = 0;
// 	temp = list;
// 	while (temp && !ft_strcmp(temp->content, "|"))
// 	{
// 		content = temp -> content;	
// 		len = ft_strlen(content);
// 		if ((content[len - 1] == '<' || content[len - 1] == '>'))
// 			flag = 1;
// 		else
// 		{
// 			if (flag == 0) //환경변수 확장했을 때 수를 더하도록 수정함 
// 				//여기서 추가로 세주기 
// 				num += count_word_with_expand(content, env_lst);
// 			flag = 0;
// 		}
// 		temp = temp -> next;
// 	}
// 	return (num);
// }

// size_t	get_word_len(char *str, size_t len, size_t temp)
// {
// 	while (str[len])
// 	{
// 		if (str[len] == '"')
// 		{
// 			temp = len;
// 			++len;
// 			while (str[len] && str[len] != '"')
// 				++len;
// 			if (str[len] == 0)
// 				len = temp;
// 		}
// 		else if (str[len] == '\'')
// 		{
// 			temp = len;
// 			++len;
// 			while (str[len] && str[len] != '\'')
// 				++len;
// 			if (str[len] == 0)
// 				len = temp;
// 		}
// 		else if (str[len] == ' ')
// 			break ;
// 		++len;
// 	}
// 	return (len);
// }

// char **split_word(char *str, int num)
// {
// 	char	**str_arr;
// 	size_t	i;
// 	size_t	j;
// 	size_t	word_len;

// 	if (str == NULL)
// 		return (NULL);
// 	str_arr = (char **)malloc(sizeof(char *) * (num + 1));
// 	i = 0;
// 	j = 0;
// 	while (i < (size_t)num)
// 	{
// 		while (str[j] == ' ')
// 			j++;
// 		word_len = get_word_len(&str[j], 0, 0);
// 		str_arr[i] = ft_substr(str, j, word_len);
// 		// ft_printf("%s\n", str_arr[i]);
// 		j += word_len;
// 		++i;
// 	}
// 	str_arr[i] = 0;
// 	return (str_arr);
// }

// void expand_and_fill_command(t_command *command, char *content, t_env *env_lst, int *j)
// {
// 	char	*temp;
// 	int		temp_num;
// 	char	**temp_arr;
// 	int		i;

// 	temp_num = count_word_with_expand(content, env_lst);
// 	temp = content;
// 	expand_env_2(&temp, env_lst);
// 	temp_arr = split_word(temp, temp_num);
// 	free(temp);
// 	i = 0;
// 	while (temp_arr[i])
// 	{
// 		(command->command)[(*j)++] = ft_strdup(check_cmd(temp_arr[i], env_lst));
// 		++i;
// 	}
// 	free(temp_arr);
// }

// t_list *handle_input_redirection(t_info *info, t_list *list, t_env *env_lst, t_command *command)
// {
// 	char	*file;

// 	file = check_cmd(list -> next -> content, env_lst);
// 	put_input(info, list, command, file);
// 	list = list -> next;
// 	return (list);
// }

// t_list *handle_output_redirection(t_info *info, t_list *list, t_env *env_lst, t_command *command)
// {
// 	char	*file;
// 	char	*content;

// 	content = list -> content;
// 	list = list -> next;
// 	file = check_cmd(list -> content, env_lst);
// 	put_output(info, content, command, file);
// 	return (list);
// }

// t_list	*check_and_init(t_list *list, t_command *command, t_env *env_lst)
// {
// 	int		num;

// 	if (((char *)list->content)[0] == '|')
// 		list = list->next;
// 	num = check_word_num(list, env_lst);
// 	init_command(command, num);
// 	return (list);
// }


// t_list	*put_command(t_info *info, t_command *command, t_list *list, t_env *env_lst)
// {
// 	int		len;
// 	char	*content;
// 	int		j;

// 	list = check_and_init(list, command, env_lst);
// 	j = 0;
// 	while (list && !ft_strcmp(list->content, "|"))
// 	{
// 		content = list -> content;
// 		len = ft_strlen(content);
// 		if (content[len - 1] == '<')
// 			list = handle_input_redirection(info, list, env_lst, command);
// 		else if (content[len - 1] == '>')
// 			list = handle_output_redirection(info, list, env_lst, command);
// 		else //환경변수 확장한 것 split해서 가져온 후 command에 넣어줌 
// 			expand_and_fill_command(command, content, env_lst, &j);
// 		list = list -> next;
// 	}
// 	return (list);
// }

t_info	*parse_command(char *command, t_env *env_lst)
{
	t_list	*list;
	t_info	*info;
	 t_list	*temp;
	// t_list	*temp2;
	int		i;

	i = 0;
	list = split_command(command);
	if (list == NULL) //syntax error 시 return NULL;
		return (NULL);
	temp = list;
	if (check_error(list)) //syntax error 시 return NULL;
	{
		ft_lstclear(&list, free);
		return (NULL); //list 다 free해줘야함 
	}
	info = malloc(sizeof(t_info));
	info->heredoc_num = 0;
	info->process_num = pipe_num(list) + 1;
	info->commands = (t_command *)malloc(sizeof(t_command) * info->process_num);
	while (i < info -> process_num)
	{
		list = put_command(info, &(info->commands[i]), list, env_lst);
		i++;
	}
	//list free?
	// while(temp)
	// {
	// 	temp2 = temp -> next;
	// 	free(temp);
	// 	temp = temp2;
	// }
	ft_lstclear(&temp, free);
	return (info);
}

static void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit_status = 1;
}

void    free_env(t_env *env_lst)
{
    t_env   *temp;
    while (env_lst)
    {
        free(env_lst->key);
        free(env_lst->value);
        temp = env_lst;
        env_lst = env_lst->next;
        free(temp);
    }
}
void    free_heredocs(t_info *info)
{
    int i = 0;
    while (info->heredocs[i])
    {
        free(info->heredocs[i]);
        ++i;
    }
    free(info->heredocs);
}

void leaks(void)
{
	system("leaks minishell");
}

//////////free_command
void	free_command(char **command)
{
	int i = 0;
	while(command[i])
		free(command[i++]);
	free(command);
}

void	free_redirect(t_redirect *rd)
{
	t_redirect *temp;
	
	while(rd)
	{
		temp = rd -> next;
		free(rd->fd);
		free(rd->file);
		free(rd);
		rd = temp;
	}
}

void	free_info_commands(t_info *info)
{
	int i = 0;

	while(i < info -> process_num)
	{
		free_command((info->commands[i]).command);
		free_redirect((info->commands[i]).input);
		free_redirect((info->commands[i]).output);
		i++;
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_env		*env_lst;
	char		*command;
	t_info		*info;
	t_process	*process;
	int			ret;

	// atexit(leaks);
	init(argc, argv, env, &env_lst);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		command = read_command();
		if (command == NULL)
			continue ;
		info = parse_command(command, env_lst);
		if (info == NULL)
			continue ;
		if (create_heredoc_temp(info, env_lst) == 0)
			continue ;
		signal(SIGINT, sigint_handler);
		if (info->process_num == 1)
		{
			int		stdin_dup;
			int		stdout_dup;
			int		stderr_dup;
			stdin_dup = dup(0);
			stdout_dup = dup(1);
			stderr_dup = dup(2);
			ret = exec_single_builtin(info, &env_lst);
			if (ret == 1)
			{
				unlink_heredocs(info);
				dup2(stdin_dup, 0);
				dup2(stdout_dup, 1);
				dup2(stderr_dup, 2);
				close(stdin_dup);
				close(stdout_dup);
				close(stderr_dup);
				exit_status = 0;
				continue ;
			}
			else if (ret == -1)
			{
				unlink_heredocs(info);
				dup2(stdin_dup, 0);
				dup2(stdout_dup, 1);
				dup2(stderr_dup, 2);
				close(stdin_dup);
				close(stdout_dup);
				close(stderr_dup);
				continue ;
			}
		}
		process = (t_process *)malloc(sizeof(t_process) * info->process_num);
		create_pipe(process, info->process_num);
		fork_and_execute(process, info, &env_lst);
		wait_all_child(info->process_num, process);
		unlink_heredocs(info);
		free(command);
		free_info_commands(info);
		free_env(env_lst);
		free_heredocs(info);
	}
}
