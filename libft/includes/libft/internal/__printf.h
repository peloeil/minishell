/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __printf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:26:58 by sota              #+#    #+#             */
/*   Updated: 2024/12/09 02:16:06 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PRINTF_H
# define __PRINTF_H

# include <libft/std_string.h>
# include <stdarg.h>
# include <stdint.h>

enum
{
	AS_PTR,
	AS_low,
	AS_UP,
};

int	__printf_push_str(const char *format, t_string *str, va_list ap);
int	__push_ch(t_string *str, size_t size, char c);
int	__push_str(t_string *str, size_t size, const char *s);
int	__push_int(t_string *str, size_t size, int n);
int	__push_uint(t_string *str, size_t size, unsigned int n);
int	__push_hex(t_string *str, size_t size, uintptr_t n, int flag);

#endif // __PRINT_H
