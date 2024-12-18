/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:25:32 by sota              #+#    #+#             */
/*   Updated: 2024/12/13 01:26:52 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_stdio.h>

int	ft_asprintf(char **strp, const char *format, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, format);
	res = ft_vasprintf(strp, format, ap);
	va_end(ap);
	return (res);
}
