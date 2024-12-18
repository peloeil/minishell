/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_fd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 01:44:32 by sota              #+#    #+#             */
/*   Updated: 2024/10/02 15:51:45 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUT_FD_H
# define FT_PUT_FD_H

int	ft_putchar_fd(char c, int fd);
int	ft_putendl_fd(char *s, int fd);
int	ft_putnbr_fd(int n, int fd);
int	ft_putstr_fd(char *s, int fd);

#endif // FT_PUT_FD_H
