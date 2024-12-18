/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:51:58 by sota              #+#    #+#             */
/*   Updated: 2024/12/03 03:39:47 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/std_string.h>
#include <stdlib.h>

int	ft_str_new(t_string *str)
{
	str->len = 0;
	str->capacity = 0;
	str->str = (char *)malloc(sizeof(char) * 1);
	if (str->str == NULL)
		return (-1);
	str->str[0] = '\0';
	return (0);
}
