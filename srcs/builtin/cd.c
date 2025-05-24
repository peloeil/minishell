/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:04:24 by marvin            #+#    #+#             */
/*   Updated: 2025/05/15 04:01:20 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_stdio.h>
#include <libft/ft_string.h>
#include <minishell/minishell.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	update_pwd_and_oldpwd2(char *new_path, char *old_path, t_envp *envp)
{
	int	pwd_flags;
	int	old_flags;
	int	status;

	status = 0;
	pwd_flags = get_env_flags("PWD", envp);
	old_flags = get_env_flags("OLDPWD", envp);
	if (old_flags != FLAG_UNSET && pwd_flags != FLAG_UNSET)
	{
		status |= add_envp_with_flag("OLDPWD", old_path, envp,
				old_flags | FLAG_EXPORT);
		status |= add_envp_with_flag("PWD", new_path, envp,
				pwd_flags | FLAG_EXPORT);
		if (status == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		else
			return (EXIT_FAILURE);
	}
	if (old_flags == FLAG_UNSET)
		status |= add_envp_with_flag("OLDPWD", old_path, envp, FLAG_UNSET);
	else
		status |= add_envp_with_flag("OLDPWD", old_path, envp, FLAG_EXPORT);
	if (pwd_flags == FLAG_UNSET)
	{
		status |= add_envp_with_flag("PWD", new_path, envp, FLAG_UNSET);
		status |= add_envp_with_flag("!PWD", new_path, envp, FLAG_HIDDEN);
	}
	else
	{
		status |= add_envp_with_flag("PWD", new_path, envp, FLAG_EXPORT);
		status |= add_envp_with_flag("!PWD", new_path, envp, FLAG_HIDDEN);
	}
	if (status == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	update_pwd_and_oldpwd(t_envp *envp)
{
	int		pwd_key;
	int		old_key;
	int		status;
	char	*new_path;
	char	*pwd_value;

	status = 0;
	new_path = getcwd(NULL, 0);
	if (!new_path)
	{
		perror("getcwd");
		return (EXIT_FAILURE);
	}
	pwd_key = ft_haskey("PWD", envp);
	old_key = ft_haskey("OLDPWD", envp);
	pwd_value = ft_getenv("!PWD", envp);
	if (!pwd_key)
	{
		status |= add_envp_with_flag("PWD", new_path, envp, FLAG_UNSET);
		status |= add_envp_with_flag("!PWD", new_path, envp, FLAG_HIDDEN);
		status |= add_envp_with_flag("OLDPWD", "", envp, FLAG_VALUE);
	}
	else if (!old_key)
	{
		status |= add_envp_with_flag("OLDPWD", pwd_value, envp, FLAG_UNSET);
		status |= add_envp_with_flag("PWD", new_path, envp, FLAG_EXPORT);
	}
	else
		status |= update_pwd_and_oldpwd2(new_path, pwd_value, envp);
	free(new_path);
	if (status == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	no_such(char *path, char *old_path)
{
	if (chdir(path) == -1)
	{
		perror("chdir");
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
		ft_dprintf(STDERR_FILENO, "-minishell: cd: too many arguments\n");
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

int	cd(int fd, char **argv, t_envp **envp)
{
	char	*old_path;
	char	*pwd_env;
	char	*new_path;
	int		result;

	(void)fd;
	new_path = NULL;
	pwd_env = ft_getenv("!PWD", *envp);
	if (pwd_env)
		old_path = ft_strdup(pwd_env);
	else
		old_path = getcwd(NULL, 0); // fallback
	result = resolve_cd_target(argv, *envp, &new_path);
	if (result != EXIT_SUCCESS)
	{
		free(old_path);
		return (result);
	}
	if (no_such(new_path, old_path) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (update_pwd_and_oldpwd(*envp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	free(old_path);
	free(new_path);
	return (EXIT_SUCCESS);
}
