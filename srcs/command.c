/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:22:05 by sota              #+#    #+#             */
/*   Updated: 2025/05/14 17:56:14 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/execute.h>
#include <libft/ft_string.h>
#include <libft/ft_stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

static int	is_not_executable(const char *cmd, struct stat statbuf)
{
	if (S_ISDIR(statbuf.st_mode))
	{
		error_return(cmd, strerror(EISDIR));
		return (1);
	}
	if (statbuf.st_mode & S_IXUSR)
		return (0);
	if (statbuf.st_mode & S_IXGRP)
		return (0);
	if (statbuf.st_mode & S_IXOTH)
		return (0);
	error_return(cmd, strerror(EACCES));
	return (1);
}

int	set_absolute_path(char **const pathptr, const char *cmd, t_envp *envp)
{
	char		*path;
	struct stat	statbuf;

	if (wrap_stat(cmd, &statbuf) == -1)
		return (-1);
	if (is_not_executable(cmd, statbuf))
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
		if (access(file, mode) == 0)
		{
			if (mode == F_OK)
				error_return(file, strerror(EACCES));
			return (file);
		}
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
