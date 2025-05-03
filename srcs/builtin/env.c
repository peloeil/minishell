/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:38:56 by marvin            #+#    #+#             */
/*   Updated: 2025/05/03 20:45:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/ft_string.h>
#include <libft/ft_stdio.h>
#include <libft/ft_put_fd.h>
#include <libft/std_string.h>
#include <stdlib.h>

int	env(int fd, t_envp *envp)
{
	t_string	str;

	if (ft_str_new(&str) == -1)
		return (1);
	while (envp != NULL)
	{
		if (envp->exported == 1)
			make_str(0, &str, envp->key, envp->value);
		envp = envp->next;
	}
	ft_dprintf(fd, "%s", str.str);
	return (0);
}
