/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_write_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-25 09:06:21 by yonuma            #+#    #+#             */
/*   Updated: 2025-05-25 09:06:21 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/ft_stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int	print_write_error(int fd, t_string str, char *name)
{
	int	i;

	i = ft_dprintf(fd, "%s", str.str);
	free(str.str);
	if (i < 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: write error: %s\n",
			name, strerror(errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
