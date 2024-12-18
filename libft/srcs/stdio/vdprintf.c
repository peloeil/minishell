/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vdprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:36:51 by sota              #+#    #+#             */
/*   Updated: 2024/12/09 02:38:50 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_stdio.h>
#include <libft/std_string.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_vdprintf(int fd, const char *format, va_list ap)
{
	char	*buf;
	int		byte;
	int		res;

	byte = ft_vasprintf(&buf, format, ap);
	if (byte == -1)
		return (-1);
	res = write(fd, buf, byte);
	free(buf);
	return (res);
}
