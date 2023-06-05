/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 23:17:10 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/05 23:34:32 by jihyeole         ###   ########.fr       */
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
