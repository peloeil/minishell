/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 04:10:30 by sota              #+#    #+#             */
/*   Updated: 2024/12/03 04:18:18 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_string.h>
#include <libft/std_string.h>

int	ft_str_find(const t_string *str, char c)
{
	char	*ptr;

	ptr = ft_strchr(str->str, c);
	if (ptr == NULL)
		return (-1);
	return (ptr - str->str);
}
