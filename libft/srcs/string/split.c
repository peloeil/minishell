/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:10:57 by sota              #+#    #+#             */
/*   Updated: 2024/06/27 01:43:47 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft/ft_string.h>

static int	is_delimiter(char c, char delim)
{
	return (c == 0 || c == delim);
}

static size_t	count_word(const char *str, char delim)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i++] != '\0')
	{
		if (is_delimiter(str[i - 1], delim))
			continue ;
		if (is_delimiter(str[i], delim))
			count++;
	}
	return (count);
}

static size_t	next_index(const char *str, char delim, int flag)
{
	size_t	res;

	res = 0;
	while (is_delimiter(str[res], delim) == flag)
		res++;
	return (res);
}

static void	free_all(char **res)
{
	size_t	i;

	i = 0;
	while (res[i] != NULL)
		free(res[i++]);
	free(res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	res_size;
	size_t	i;
	size_t	offset;
	size_t	str_len;

	if (s == NULL)
		return (NULL);
	res_size = count_word(s, c);
	res = (char **)malloc(sizeof(char *) * (res_size + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	offset = 0;
	while (i < res_size)
	{
		offset += next_index(s + offset, c, 1);
		str_len = next_index(s + offset, c, 0);
		res[i] = ft_strndup(s + offset, str_len);
		if (res[i++] == NULL)
			return (free_all(res), NULL);
		offset += str_len;
	}
	res[res_size] = 0;
	return (res);
}
