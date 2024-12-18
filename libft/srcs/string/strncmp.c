/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 06:22:50 by sota              #+#    #+#             */
/*   Updated: 2024/08/25 00:51:19 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;
	int				diff;

	i = 0;
	while (i < n)
	{
		c1 = s1[i];
		c2 = s2[i];
		diff = c1 - c2;
		if (c1 == '\0' || diff != 0)
			return (diff);
		i++;
	}
	return (0);
}
