/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:41:09 by sota              #+#    #+#             */
/*   Updated: 2024/12/09 02:26:27 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/std_string.h>
#include <libft/internal/__printf.h>

int	__push_str(t_string *str, size_t size, const char *s)
{
	size_t	i;

	if (s == NULL)
		return (__push_str(str, size, "(null)"));
	i = 0;
	while (s[i] != '\0')
	{
		if (__push_ch(str, size, s[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
