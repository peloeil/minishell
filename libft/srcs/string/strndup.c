/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strndup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:38:29 by sota              #+#    #+#             */
/*   Updated: 2024/12/13 00:59:18 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft/ft_string.h>

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	len;
	char	*res;

	len = ft_strlen(s1);
	if (n >= len)
		n = len;
	res = (char *)malloc(sizeof(char) * (n + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, n + 1);
	return (res);
}
