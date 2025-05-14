/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 05:26:30 by yonuma            #+#    #+#             */
/*   Updated: 2025/05/15 03:55:30 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libft/ft_stdio.h>

int	pwd(int fd, char **argv, t_envp **envp)
{
	char	*cwd;

	(void)argv;
	(void)envp;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd");
		return (1);
	}
	ft_dprintf(fd, "%s\n", cwd);
	free(cwd);
	return (0);
}
