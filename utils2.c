/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 23:17:10 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/17 14:57:57 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	jh_strcmp(char	*s1, char *s2)
{
	size_t			idx;
	unsigned char	*c1;
	unsigned char	*c2;

	idx = 0;
	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (*(c1 + idx) == *(c2 + idx))
	{
		if (*(c1 + idx) == 0)
			return (0);
		++idx;
	}
	return (*(c1 + idx) - *(c2 + idx));
}

static int	ft_isblank(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	else if (c == '\f' || c == '\n' || c == '\r')
		return (1);
	else
		return (0);
}

long long	ft_atol(const char *str)
{
	long long	result;
	int			is_positive;

	result = 0;
	is_positive = 1;
	while (ft_isblank(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		is_positive = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * is_positive);
}

void	env_lstdelone(t_env *lst)
{
	if (lst == NULL)
		return ;
	free(lst->key);
	free(lst->value);
	free(lst);
}

void	save_file_name(t_redirect *input, t_redirect *redirect, char *tempfile)
{
	free(input->file);
	free(redirect->file);
	input->file = tempfile;
	redirect->file = ft_strdup(tempfile);
}
