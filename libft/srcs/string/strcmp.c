/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:33:10 by sota              #+#    #+#             */
/*   Updated: 2024/12/12 23:15:08 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include <libft/ft_string.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	return (ft_strncmp(s1, s2, SIZE_MAX));
}
