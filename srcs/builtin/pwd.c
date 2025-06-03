/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 05:26:30 by yonuma            #+#    #+#             */
/*   Updated: 2025/06/03 21:53:14 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/execute.h>
#include <libft/ft_stdio.h>

int	pwd(int fd, char **argv, t_envp **envp)
{
	char	*cwd;

	(void)argv;
	(void)envp;
	cwd = ft_getenv("!PWD", *envp);
	if (ft_dprintf(fd, "%s\n", cwd) < 0)
		return (STATUS_ERRORS);
	return (STATUS_SUCCESS);
}
