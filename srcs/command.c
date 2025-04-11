/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:22:05 by sota              #+#    #+#             */
/*   Updated: 2025/04/10 13:56:42 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/ft_string.h>
#include <libft/ft_stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	set_cmd_path(char **const path_ptr, const char *cmd, const char **envp)
{
	char	*env_path;
	char	**path_dirs;
	size_t	i;

	// if (ft_strcmp(cmd, "pwd") == 0)
	// 	return (pwd(path_ptr));
	env_path = ft_getenv("PATH", envp);
	if (env_path == NULL)
		return (-1);
	path_dirs = ft_split(env_path, ':');
	if (path_dirs == NULL)
		return (-1);
	i = 0;
	while (path_dirs[i] != NULL)
	{
		if (ft_asprintf(path_ptr, "%s/%s", path_dirs[i], cmd) == -1)
			return (-1);
		if (access(*path_ptr, F_OK | X_OK) != 0)
		{
			free(*path_ptr);
			*path_ptr = NULL;
			i++;
			continue ;
		}
		break ;
		i++;
	}
	free_strs((const char **)path_dirs);
	return (0);
}
