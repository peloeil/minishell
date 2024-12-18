/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:05:32 by sota              #+#    #+#             */
/*   Updated: 2024/12/05 18:08:57 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_stdio.h>

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, format);
	res = ft_vsnprintf(str, size, format, ap);
	va_end(ap);
	return (res);
}
