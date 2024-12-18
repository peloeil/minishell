/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdio.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:05:10 by sota              #+#    #+#             */
/*   Updated: 2024/12/08 18:01:37 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDIO_H
# define FT_STDIO_H

# include <unistd.h>
# include <stdarg.h>

# define BUFFER_SIZE 4096

int		ft_vdprintf(int fd, const char *format, va_list ap);
int		ft_vprintf(const char *format, va_list ap);
int		ft_vsprintf(char *str, const char *format, va_list ap);
int		ft_vsnprintf(char *str, size_t size, const char *format, va_list ap);
int		ft_vasprintf(char **strp, const char *format, va_list ap);
int		ft_dprintf(int fd, const char *format, ...)
		__attribute__((format(printf, 2, 3)));
int		ft_printf(const char *format, ...)
		__attribute__((format(printf, 1, 2)));
int		ft_sprintf(char *str, const char *format, ...)
		__attribute__((format(printf, 2, 3)));
int		ft_snprintf(char *str, size_t size, const char *format, ...)
		__attribute__((format(printf, 3, 4)));
int		ft_asprintf(char **strp, const char *format, ...)
		__attribute__((format(printf, 2, 3)));

int		ft_getc(int fd);
ssize_t	ft_getdelim(char **lineptr, size_t *n, int delim, int fd);
ssize_t	ft_getline(char **lineptr, size_t *n, int fd);

#endif // FT_STDIO_H
