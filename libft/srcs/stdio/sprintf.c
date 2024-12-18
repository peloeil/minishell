/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprintf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:05:32 by sota              #+#    #+#             */
/*   Updated: 2024/12/05 18:07:28 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_stdio.h>

int	ft_sprintf(char *str, const char *format, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, format);
	res = ft_vsprintf(str, format, ap);
	va_end(ap);
	return (res);
}
