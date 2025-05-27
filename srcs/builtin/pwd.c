/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 05:26:30 by yonuma            #+#    #+#             */
/*   Updated: 2025/05/27 14:27:32 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/execute.h>
#include <stdlib.h>
#include <libft/ft_stdio.h>

int	pwd(int fd, char **argv, t_envp **envp)
{
	char	*cwd;
	int		need_free;
	int		status;

	(void)argv;
	(void)envp;
	status = STATUS_SUCCESS;
	need_free = 1;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		cwd = ft_getenv("!PWD", *envp);
		need_free = 0;
	}
	if (ft_dprintf(fd, "%s\n", cwd) < 0)
		status = STATUS_ERRORS;
	if (need_free)
		free(cwd);
	return (status);
}
