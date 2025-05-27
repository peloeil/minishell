/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:38:56 by marvin            #+#    #+#             */
/*   Updated: 2025/05/27 20:07:09 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/execute.h>
#include <libft/ft_stdio.h>
#include <stdlib.h>

int	env(int fd, char **argv, t_envp **envp)
{
	int			i;
	t_string	str;
	t_envp		*tmp_envp;

	(void)argv;
	if (ft_str_new(&str) == -1)
		return (STATUS_ERRORS);
	tmp_envp = *envp;
	while (tmp_envp != NULL)
	{
		if ((tmp_envp->exported & FLAG_EXPORT)
			&& make_str(0, &str, tmp_envp->key, tmp_envp->value) == -1)
			return (STATUS_ERRORS);
		tmp_envp = tmp_envp->next;
	}
	i = ft_dprintf(fd, "%s", str.str);
	free(str.str);
	if (i < 0)
		return (STATUS_ERRORS);
	return (STATUS_SUCCESS);
}
