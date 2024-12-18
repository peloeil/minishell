/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_string.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:49:48 by sota              #+#    #+#             */
/*   Updated: 2024/12/06 11:56:49 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STD_STRING_H
# define STD_STRING_H

# include <stddef.h>

typedef struct s_string
{
	char	*str;
	size_t	len;
	size_t	capacity;
}	t_string;

// str->str が確保されていないことが保証されている場合にのみ使う
int	ft_str_new(t_string *str);
int	ft_str_with_capacity(t_string *str, size_t capacity);
int	ft_str_from(t_string *str, const char *s);

// str->str が確保されていることが保証されている場合にのみ使う
int	ft_str_reserve(t_string *str, size_t additional);
int	ft_str_push(t_string *str, char c);
int	ft_str_push_str(t_string *str, const char *s);
int	ft_str_pop(t_string *str);
int	ft_str_insert(t_string *str, size_t idx, char c);
int	ft_str_starts_with(const t_string *str, const char *prefix);
int	ft_str_ends_with(const t_string *str, const char *suffix);
int	ft_str_find(const t_string *str, char c);
int	ft_str_rfind(const t_string *str, char c);

#endif // STD_STRING_H
