/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:00:32 by sota              #+#    #+#             */
/*   Updated: 2024/06/27 01:48:13 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <libft/ft_string.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < (size_t)start)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	return (ft_strndup(s + start, len));
}
