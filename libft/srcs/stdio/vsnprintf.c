/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vsnprintf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:02:49 by sota              #+#    #+#             */
/*   Updated: 2024/12/13 01:26:40 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/internal/__printf.h>
#include <libft/std_string.h>
#include <libft/ft_string.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdint.h>

static int	is_ordinal_specifier(char c)
{
	return (c == 'c'
		|| c == 's'
		|| c == 'p'
		|| c == 'd'
		|| c == 'i'
		|| c == 'u'
		|| c == 'x'
		|| c == 'X');
}

static size_t	is_specifier(const char *format, size_t i)
{
	int		flag;

	if (i == 0 || format[i - 1] != '%')
		return (0);
	if (format[i] != '%' && !is_ordinal_specifier(format[i]))
		return (0);
	flag = 0;
	while (i--)
	{
		if (format[i] != '%')
			break ;
		flag ^= 1;
	}
	return (flag);
}

static int	push_to_buf(t_string *str, size_t size, char c, va_list ap)
{
	if ((c == '%' && __push_ch(str, size, c) == -1)
		|| (c == 'c' && __push_ch(str, size, va_arg(ap, int)) == -1)
		|| (c == 's' && __push_str(str, size, va_arg(ap, char *)) == -1)
		|| (c == 'p'
			&& __push_hex(str, size, va_arg(ap, uintptr_t), AS_PTR) == -1)
		|| (c == 'd' && __push_int(str, size, va_arg(ap, int)) == -1)
		|| (c == 'i' && __push_int(str, size, va_arg(ap, int)) == -1)
		|| (c == 'u' && __push_uint(str, size, va_arg(ap, int)) == -1)
		|| (c == 'x'
			&& __push_hex(str, size, va_arg(ap, unsigned int), AS_low) == -1)
		|| (c == 'X'
			&& __push_hex(str, size, va_arg(ap, unsigned int), AS_UP) == -1))
		return (-1);
	return (0);
}

int	ft_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	t_string	s;
	size_t		i;

	s.str = str;
	s.len = 0;
	s.capacity = SIZE_MAX;
	i = 0;
	while (format[i] != '\0')
	{
		if (is_specifier(format, i)
			&& push_to_buf(&s, size, format[i], ap) == -1)
			return (-1);
		if (!is_specifier(format, i) && format[i] != '%'
			&& __push_ch(&s, size, format[i]) == -1)
			return (-1);
		i++;
	}
	return (s.len);
}
