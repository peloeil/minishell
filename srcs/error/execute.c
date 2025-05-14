/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:19:31 by sota              #+#    #+#             */
/*   Updated: 2025/05/15 03:12:32 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_stdio.h>

int	error_return(const char *name, const char *msg)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", name, msg);
	return (-1);
}
