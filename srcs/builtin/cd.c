/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:04:24 by marvin            #+#    #+#             */
/*   Updated: 2025/05/13 19:30:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_stdio.h>
#include <libft/ft_string.h>
#include <minishell/minishell.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	add_envp_with_flag(char *key, char *value, t_envp *envp,
		int flags)
{
	t_envp	*current;
	t_envp	*new_node;

	current = envp;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			current->exported = flags;
			return ;
		}
		if (current->next == NULL)
			break ;
		current = current->next;
	}
	new_node = create_new_node(ft_strdup(key), ft_strdup(value), flags);
	if (!new_node)
	{
		free(key);
		free(value);
		return ;
	}
	current->next = new_node;
}

void	update_env_value(const char *key, const char *value, t_envp *envp)
{
	t_envp	*current;

	current = envp;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
}

int	get_env_flags(const char *key, t_envp *envp)
{
	t_envp	*current;

	current = envp;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->exported);
		current = current->next;
	}
	return (-1);
}

void	update_pwd_and_oldpwd2(char *new_path, char *old_path, t_envp *envp)
{
	int	pwd_flags;
	int	old_flags;

	pwd_flags = get_env_flags("PWD", envp);
	old_flags = get_env_flags("OLDPWD", envp);
	if (old_flags == FLAG_UNSET)
		add_envp_with_flag("OLDPWD", old_path, envp, FLAG_UNSET);
	else
		add_envp_with_flag("OLDPWD", old_path, envp, old_flags);
	if (pwd_flags == FLAG_UNSET)
		add_envp_with_flag("PWD", new_path, envp, FLAG_UNSET);
	else
		add_envp_with_flag("PWD", new_path, envp, FLAG_EXPORT);
}

void	update_pwd_and_oldpwd(t_envp *envp, char *old_path)
{
	char	*new_path;
	char	*pwd_value;
	char	*old_value;

	new_path = getcwd(NULL, 0);
	pwd_value = ft_getenv("PWD", envp);
	old_value = ft_getenv("OLDPWD", envp);
	if (!pwd_value)
	{
		add_envp_with_flag("PWD", new_path, envp, FLAG_UNSET);
		add_envp_with_flag("OLDPWD", "", envp, FLAG_EXPORT);
	}
	else if (!old_value)
	{
		add_envp_with_flag("OLDPWD", old_path, envp, FLAG_UNSET);
		add_envp_with_flag("PWD", new_path, envp, FLAG_EXPORT);
	}
	else
		update_pwd_and_oldpwd2(new_path, old_path, envp);
	free(new_path);
}

int	no_such(char *path, char *old_path)
{
	if (chdir(path) == -1)
	{
		ft_dprintf(STDERR_FILENO, "cd: %s: No such file or directory\n", path);
		free(old_path);
		free(path);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	resolve_cd_target(char **argv, t_envp *envp, char **out_path)
{
	char	*home_path;

	if (count_argv(argv) > 2)
	{
		ft_dprintf(STDERR_FILENO, "-minishel: cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	if (argv[1] == NULL)
	{
		home_path = ft_getenv("HOME", envp);
		if (home_path == NULL)
		{
			ft_dprintf(STDERR_FILENO, "cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
		*out_path = ft_strdup(home_path);
	}
	else
		*out_path = ft_strdup(argv[1]);
	if (*out_path == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	cd(char **argv, t_envp *envp)
{
	char	*old_path;
	char	*new_path;
	int		result;

	old_path = NULL;
	new_path = NULL;
	result = resolve_cd_target(argv, envp, &new_path);
	if (result != EXIT_SUCCESS)
		return (result);
	old_path = getcwd(NULL, 0);
	if (no_such(new_path, old_path) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	update_pwd_and_oldpwd(envp, old_path);
	free(old_path);
	free(new_path);
	return (EXIT_SUCCESS);
}
