/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:04:24 by marvin            #+#    #+#             */
/*   Updated: 2025/05/30 14:37:48 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/execute.h>
#include <libft/ft_string.h>
#include <libft/ft_stdio.h>
#include <stdlib.h>

static char	*cd_target(char **argv, t_envp *envp)
{
	char	*target;

	if (count_argv(argv) > 2)
	{
		error_return(0, "cd", "too many arguments");
		return (NULL);
	}
	target = argv[1];
	if (target == NULL)
		target = ft_getenv("HOME", envp);
	if (target == NULL)
	{
		error_return(0, "cd", "HOME not set");
		return (NULL);
	}
	return (ft_strdup(target));
}

static int	update_oldpwd(const char *path, t_envp **envp)
{
	char	*str;
	int		flag;
	int		failed;

	flag = (FLAG_EXPORT | FLAG_ENV);
	if (ft_getenv("PWD", *envp) == NULL)
	{
		str = ft_strdup("OLDPWD=");
		if (str == NULL)
			return (-1);
		flag = FLAG_EXPORT;
	}
	else
	{
		if (ft_asprintf(&str, "OLDPWD=%s", path) == -1)
			return (-1);
		if (ft_getenv("OLDPWD", *envp) == NULL)
			flag = FLAG_SPECIAL;
	}
	failed = (update_ms_envp(envp, str, flag) == -1);
	free(str);
	if (failed)
		return (-1);
	return (0);
}

static int	update_internal_pwd(const char *path, t_envp **envp)
{
	char	*str;
	int		failed;

	if (ft_asprintf(&str, "!PWD=%s", path) == -1)
		return (-1);
	failed = (update_ms_envp(envp, str, FLAG_SPECIAL) == -1);
	free(str);
	if (failed)
		return (-1);
	return (0);
}

static int	update_pwd(const char *path, t_envp **envp)
{
	char	*str;
	t_envp	*pwd_node;
	int		flag;
	int		failed;

	if (ft_asprintf(&str, "PWD=%s", path) == -1)
		return (-1);
	pwd_node = search_key("PWD", *envp);
	flag = (FLAG_EXPORT | FLAG_ENV);
	if (pwd_node == NULL || (pwd_node->flag & FLAG_SPECIAL))
		flag = FLAG_SPECIAL;
	failed = (update_ms_envp(envp, str, flag) == -1);
	free(str);
	if (failed)
		return (-1);
	return (0);
}

int	cd(int fd, char **argv, t_envp **envp)
{
	char	*old_path;
	char	*new_path;
	int		failed;

	(void)fd;
	old_path = ft_strdup(ft_getenv("!PWD", *envp));
	new_path = cd_target(argv, *envp);
	failed = (old_path == NULL || new_path == NULL
			|| wrap_chdir(new_path) == -1
			|| update_oldpwd(old_path, envp) == -1
			|| update_internal_pwd(new_path, envp) == -1
			|| update_pwd(new_path, envp) == -1);
	free(old_path);
	free(new_path);
	if (failed)
		return (STATUS_ERRORS);
	return (STATUS_SUCCESS);
}
