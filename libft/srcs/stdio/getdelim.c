/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getdelim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:05:01 by sota              #+#    #+#             */
/*   Updated: 2024/12/06 12:02:36 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/std_string.h>
#include <libft/ft_string.h>
#include <libft/ft_stdio.h>
#include <stdio.h>
#include <unistd.h>

static int	init_string(t_string *str, char *ptr, size_t n)
{
	if (ptr == NULL || n == 0)
		return (ft_str_new(str));
	str->len = 0;
	str->capacity = n - 1;
	str->str = ptr;
	str->str[0] = '\0';
	return (0);
}

ssize_t	ft_getdelim(char **lineptr, size_t *n, int delim, int fd)
{
	t_string	str;
	char		ch;

	if (lineptr == NULL || n == NULL || fd < 0)
		return (-1);
	if (init_string(&str, *lineptr, *n) == -1)
		return (-1);
	while (1)
	{
		ch = ft_getc(fd);
		if (ch == EOF)
		{
			*lineptr = str.str;
			*n = str.len;
			return (-1);
		}
		if (ft_str_push(&str, ch) == -1)
			return (-1);
		if (ch == (char)delim)
			break ;
	}
	*lineptr = str.str;
	*n = str.len;
	return (str.len);
}
