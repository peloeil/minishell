/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:04:24 by marvin            #+#    #+#             */
/*   Updated: 2025/06/29 12:05:25 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <libft/ft_stdio.h>
#include <libft/ft_string.h>
#include <minishell/execute.h>
#include <minishell/minishell.h>
#include <stdlib.h>
#include <string.h>

static char	*cd_target(int fd, char **argv, t_envp *envp)
{
	char	*target;

	if (count_argv(argv) > 2)
	{
		error_return(0, "cd", "too many arguments");
		return (NULL);
	}
	target = argv[1];
	if (argv[1] == NULL)
		target = ft_getenv("HOME", envp);
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		target = ft_getenv("OLDPWD", envp);
		if (target != NULL)
			ft_dprintf(fd, "%s\n", target);
	}
	if (target == NULL)
	{
		if (argv[1] == NULL && search_key("HOME", envp) == NULL)
			error_return(0, "cd", "HOME not set");
		if (argv[1] != NULL && ft_strcmp(argv[1], "-") == 0)
			error_return(0, "cd", "OLDPWD not set");
		return (NULL);
	}
	return (ft_strdup(target));
}

static int	update_oldpwd(t_envp **envp)
{
	int		flag;
	char	*str;
	t_envp	*oldpwd_node;

	oldpwd_node = search_key("PWD", *envp);
	flag = (FLAG_EXPORT | FLAG_ENV);
	if (oldpwd_node == NULL || oldpwd_node->value == NULL)
	{
		if (oldpwd_node == NULL)
			flag = FLAG_EXPORT;
		if (oldpwd_node != NULL && oldpwd_node->value == NULL)
			flag = FLAG_SPECIAL;
		if (ft_asprintf(&str, "OLDPWD=") == -1)
			return (-1);
	}
	else
	{
		if (ft_asprintf(&str, "OLDPWD=%s", oldpwd_node->value) == -1)
			return (-1);
		if (oldpwd_node == NULL || (oldpwd_node->flag & FLAG_SPECIAL))
			flag = FLAG_SPECIAL;
	}
	if (update_ms_envp(envp, str, flag) == -1)
		return (free(str), -1);
	return (free(str), 0);
}

static int	update_internal_pwd(t_envp **envp)
{
	char	*path;
	char	*str;
	int		failed;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (error_return(-1, "getcwd", strerror(errno)));
	failed = (ft_asprintf(&str, "!PWD=%s", path) == -1);
	free(path);
	if (failed)
		return (-1);
	failed = (update_ms_envp(envp, str, FLAG_SPECIAL) == -1);
	free(str);
	if (failed)
		return (-1);
	return (0);
}

static int	update_pwd(t_envp **envp)
{
	char	*path;
	char	*str;
	t_envp	*pwd_node;
	int		flag;
	int		failed;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (error_return(-1, "getcwd", strerror(errno)));
	failed = (ft_asprintf(&str, "PWD=%s", path) == -1);
	free(path);
	if (failed)
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

	old_path = ft_strdup(ft_getenv("!PWD", *envp));
	new_path = cd_target(fd, argv, *envp);
	failed = (old_path == NULL || new_path == NULL || wrap_chdir(new_path) == -1
			|| update_oldpwd(envp) == -1 || update_internal_pwd(envp) == -1
			|| update_pwd(envp) == -1);
	free(old_path);
	free(new_path);
	if (failed)
		return (STATUS_ERRORS);
	return (STATUS_SUCCESS);
}
