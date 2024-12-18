/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vsprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:02:49 by sota              #+#    #+#             */
/*   Updated: 2024/12/09 02:39:59 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_stdio.h>
#include <stdint.h>

int	ft_vsprintf(char *str, const char *format, va_list ap)
{
	return (ft_vsnprintf(str, SIZE_MAX, format, ap));
}
