/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdlib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:32:31 by sota              #+#    #+#             */
/*   Updated: 2024/06/27 01:49:56 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDLIB_H
# define FT_STDLIB_H

# include <stddef.h>

int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);

char	*ft_itoa(int n);

#endif // FT_STDLIB_H
