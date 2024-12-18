/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:44:46 by sota              #+#    #+#             */
/*   Updated: 2024/06/27 01:47:00 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <libft/ft_string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;
	size_t	haystack_len;

	if (haystack == NULL && len == 0)
		return (NULL);
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	haystack_len = ft_strlen(haystack);
	if (len > haystack_len)
		len = haystack_len;
	i = 0;
	while (i + needle_len <= len)
	{
		if (ft_strncmp(haystack + i, needle, needle_len) == 0)
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
