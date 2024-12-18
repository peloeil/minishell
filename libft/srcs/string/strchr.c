/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:10:58 by sota              #+#    #+#             */
/*   Updated: 2024/12/13 01:06:37 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*res;

	i = 0;
	res = NULL;
	while (1)
	{
		if (s[i] == (unsigned char)c)
		{
			res = (char *)s + i;
			break ;
		}
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (res);
}
