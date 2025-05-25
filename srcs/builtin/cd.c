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

int	update_pwd_and_oldpwd3(char *new_path, char *old_path, t_envp *envp)
{
	int	s;
	int	pwd_flags;
	int	old_flags;

	s = 0;
	pwd_flags = get_env_flags("PWD", envp);
	old_flags = get_env_flags("OLDPWD", envp);
	if (old_flags == FLAG_UNSET)
		s |= add_with_flag("OLDPWD", old_path, envp, FLAG_UNSET);
	else
		s |= add_with_flag("OLDPWD", old_path, envp, FLAG_EXPORT);
	if (pwd_flags == FLAG_UNSET)
	{
		s |= add_with_flag("PWD", new_path, envp, FLAG_UNSET);
		s |= add_with_flag("!PWD", new_path, envp, FLAG_HIDDEN);
	}
	else
	{
		s |= add_with_flag("PWD", new_path, envp, FLAG_EXPORT);
		s |= add_with_flag("!PWD", new_path, envp, FLAG_HIDDEN);
	}
	return (s);
}

int	update_pwd_and_oldpwd2(char *new_path, char *old_path, t_envp *envp)
{
	int	pwd_flags;
	int	old_flags;
	int	s;

	s = 0;
	pwd_flags = get_env_flags("PWD", envp);
	old_flags = get_env_flags("OLDPWD", envp);
	if (old_flags != FLAG_UNSET && pwd_flags != FLAG_UNSET)
	{
		s |= add_with_flag("OLDPWD", old_path, envp, old_flags | FLAG_EXPORT);
		s |= add_with_flag("PWD", new_path, envp, pwd_flags | FLAG_EXPORT);
	}
	else
		s |= update_pwd_and_oldpwd3(new_path, old_path, envp);
	if (s == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	update_pwd_and_oldpwd(t_envp *envp, char *new_path, char *pwd_value)
{
	int	s;

	s = 0;
	if (!ft_haskey("PWD", envp))
	{
		s |= add_with_flag("PWD", new_path, envp, FLAG_UNSET);
		s |= add_with_flag("!PWD", new_path, envp, FLAG_HIDDEN);
		s |= add_with_flag("OLDPWD", "", envp, FLAG_VALUE);
	}
	else if (!ft_haskey("OLDPWD", envp))
	{
		s |= add_with_flag("OLDPWD", pwd_value, envp, FLAG_UNSET);
		s |= add_with_flag("PWD", new_path, envp, FLAG_EXPORT);
	}
	else
		s |= update_pwd_and_oldpwd2(new_path, pwd_value, envp);
	return (s);
}

int	update_pwd_and_oldpwd_base(t_envp *envp)
{
	int		s;
	char	*new_path;
	char	*pwd_value;

	s = 0;
	new_path = getcwd(NULL, 0);
	if (!new_path)
	{
		perror("getcwd");
		return (EXIT_FAILURE);
	}
	pwd_value = ft_getenv("!PWD", envp);
	update_pwd_and_oldpwd(envp, new_path, pwd_value);
	free(new_path);
	if (s == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
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
		old_path = getcwd(NULL, 0);
	result = resolve_cd_target(argv, *envp, &new_path);
	if (result != EXIT_SUCCESS)
	{
		free(old_path);
		return (result);
	}
	if (no_such(new_path, old_path) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (update_pwd_and_oldpwd_base(*envp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	free(old_path);
	free(new_path);
	return (EXIT_SUCCESS);
}
