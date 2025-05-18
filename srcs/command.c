/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:22:05 by sota              #+#    #+#             */
/*   Updated: 2025/05/18 20:11:55 by sota             ###   ########.fr       */
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


static int	found_suitable_file(const char *path, int flag, int show_error)
{
	struct stat	statbuf;

	if (access(path, F_OK) == -1)
	{
		if (show_error)
			error_return(path, strerror(ENOENT));
		return (0);
	}
	if (wrap_stat(path, &statbuf) == -1)
		return (0);
	if (S_ISDIR(statbuf.st_mode))
	{
		if (show_error)
			error_return(path, strerror(EISDIR));
		return (0);
	}
	if (flag == F_OK)
		return (1);
	if (flag == X_OK && (statbuf.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
		return (1);
	error_return(path, strerror(EACCES));
	return (0);
}

static int	set_absolute_path(char **const pathptr, const char *cmd)
{
	char		*path;

	if (!found_suitable_file(cmd, F_OK, 1))
		return (STATUS_CMD_NOT_FOUND);
	if (!found_suitable_file(cmd, X_OK, 1))
		return (STATUS_NOT_EXECUTABLE);
	path = ft_strdup(cmd);
	if (path == NULL)
		return (-1);
	free(*pathptr);
	*pathptr = path;
	return (0);
}

static char	*search_file(const char *cmd, char **dirs, int mode)
{
	size_t	i;
	char	*file;

	i = 0;
	while (dirs[i] != NULL)
	{
		if (ft_asprintf(&file, "%s/%s", dirs[i], cmd) == -1)
			return (NULL);
		if (found_suitable_file(file, mode, 0))
		{
			if (mode == F_OK)
				error_return(file, strerror(EACCES));
			return (file);
		}
		free(file);
		i++;
	}
	if (mode == F_OK)
		error_return(cmd, "command not found");
	return (NULL);
}

int	set_command_path(char **const pathptr, const char *cmd, t_envp *envp)
{
	char	*path;
	char	**dirs;
	char	*file;

	if (ft_strchr(cmd, '/') != NULL)
		return (set_absolute_path(pathptr, cmd));
	path = ft_getenv("PATH", envp);
	dirs = ft_split(path, ':');
	if (path == NULL || dirs == NULL)
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
	if (file == NULL)
		return (STATUS_CMD_NOT_FOUND);
	free(file);
	return (STATUS_NOT_EXECUTABLE);
}
