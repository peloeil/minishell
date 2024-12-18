/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   striteri.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:11:01 by sota              #+#    #+#             */
/*   Updated: 2024/06/27 01:44:37 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <libft/ft_string.h>

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;
	size_t	s_len;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	s_len = ft_strlen(s);
	while (i < s_len)
	{
		f(i, &s[i]);
		i++;
	}
}
