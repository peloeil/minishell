/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:06:35 by sota              #+#    #+#             */
/*   Updated: 2024/12/06 10:20:07 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_stdio.h>
#include <stdio.h>

int	ft_getc(int fd)
{
	static char		buf[BUFFER_SIZE];
	static size_t	index = 0;
	static ssize_t	rest = 0;

	if (rest == 0)
	{
		rest = read(fd, buf, BUFFER_SIZE);
		index = 0;
		if (rest <= 0)
			return (EOF);
	}
	rest--;
	return ((unsigned char)buf[index++]);
}
