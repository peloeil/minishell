/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:38:56 by marvin            #+#    #+#             */
/*   Updated: 2025/05/15 04:15:49 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/ft_string.h>
#include <libft/ft_stdio.h>
#include <libft/ft_put_fd.h>
#include <libft/std_string.h>
#include <stdlib.h>

int	env(int fd, char **argv, t_envp **envp)
{
	t_string	str;
	t_envp		*tmp_envp;

	(void)argv;
	if (ft_str_new(&str) == -1)
		return (1);
	tmp_envp = *envp;
	while (tmp_envp != NULL)
	{
		if (tmp_envp->exported & FLAG_EXPORT)
			make_str(0, &str, tmp_envp->key, tmp_envp->value);
		tmp_envp = tmp_envp->next;
	}
	ft_dprintf(fd, "%s", str.str);
	free(str.str);
	return (0);
}
