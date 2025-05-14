/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:22:05 by sota              #+#    #+#             */
/*   Updated: 2025/05/14 15:23:21 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/execute.h>
#include <libft/ft_string.h>
#include <libft/ft_stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int	set_absolute_path(char **const pathptr, const char *cmd, t_envp *envp)
{
	char	*path;

	if (wrap_access(cmd, F_OK) == -1 && errno == EACCES)
		return (update_exit_status(STATUS_NOT_EXECUTABLE, envp));
	if (wrap_access(cmd, X_OK) == -1 && errno == EACCES)
		return (update_exit_status(STATUS_NOT_EXECUTABLE, envp));
	path = ft_strdup(cmd);
	if (path == NULL)
		return (-1);
	free(*pathptr);
	*pathptr = path;
	return (0);
}

char	*search_file(const char *cmd, char **dirs, int mode)
{
	size_t	i;
	char	*file;

	i = 0;
	while (dirs[i] != NULL)
	{
		if (ft_asprintf(&file, "%s/%s", dirs[i], cmd) == -1)
			return (NULL);
		if (wrap_access(file, mode) == 0)
			return (file);
		free(file);
		i++;
	}
	return (NULL);
}

int	set_command_path(char **const pathptr, const char *cmd, t_envp *envp)
{
	char	*path;
	char	**dirs;
	char	*file;

	if (ft_strchr(cmd, '/') != NULL)
		return (set_absolute_path(pathptr, cmd, envp));
	path = ft_getenv("PATH", envp);
	if (path == NULL)
		return (-1);
	dirs = ft_split(path, ':');
	if (dirs == NULL)
		return (-1);
	file = search_file(cmd, dirs, X_OK);
	if (file != NULL)
	{
		free_strs(dirs);
		free(*pathptr);
		*pathptr = file;
		return (0);
	}
	file = search_file(cmd, dirs, F_OK);
	free_strs(dirs);
	return (update_exit_status(STATUS_CMD_NOT_FOUND, envp));
}
