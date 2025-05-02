/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:22:05 by sota              #+#    #+#             */
/*   Updated: 2025/05/03 00:38:06 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/ft_string.h>
#include <libft/ft_stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int	try_paths(char **const path_ptr, const char *cmd, char **path_dirs)
{
	size_t	i;

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
		return (0);
		i++;
	}
	return (-1);
}

int	set_cmd_path(char **const path_ptr, const char *cmd, const t_envp *envp)
{
	char	*env_path;
	char	**path_dirs;
	int		result;

	env_path = ft_getenv("PATH", envp);
	if (env_path == NULL)
		return (-1);
	path_dirs = ft_split(env_path, ':');
	if (path_dirs == NULL)
		return (-1);
	result = try_paths(path_ptr, cmd, path_dirs);
	free_strs((const char **)path_dirs);
	return (result);
}
