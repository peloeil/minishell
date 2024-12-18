/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:25:58 by sota              #+#    #+#             */
/*   Updated: 2024/12/06 10:28:01 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_stdio.h>
#include <unistd.h>

ssize_t	ft_getline(char **lineptr, size_t *n, int fd)
{
	return (ft_getdelim(lineptr, n, '\n', fd));
}
