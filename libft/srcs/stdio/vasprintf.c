/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vasprintf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:52:14 by sota              #+#    #+#             */
/*   Updated: 2024/12/08 18:37:17 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/internal/__printf.h>
#include <libft/std_string.h>
#include <libft/ft_stdio.h>
#include <stdlib.h>

int	ft_vasprintf(char **strp, const char *format, va_list ap)
{
	va_list	ap2;
	int		byte;

	va_copy(ap2, ap);
	byte = ft_vsnprintf(NULL, 0, format, ap2);
	va_end(ap2);
	if (byte < 0)
		return (-1);
	*strp = (char *)malloc(sizeof(char) * ((size_t)byte + 1));
	if (*strp == NULL)
		return (-1);
	return (ft_vsnprintf(*strp, (size_t)byte + 1, format, ap));
}
