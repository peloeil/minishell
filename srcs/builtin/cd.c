/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:52:46 by marvin            #+#    #+#             */
/*   Updated: 2025/04/27 17:52:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell/minishell.h>
# include <stdlib.h>
# include <libft/ft_string.h>
# include <stdio.h>
# include <unistd.h>

# include <libft/ft_stdio.h>

int count_argv(char **argv)
{
    int count;

    count = 0;
    while (argv[count] != NULL)
        count++;

    return (count);
}

char *minishell_getenv(const char *key, t_minishell_envp *envp)
{
	t_minishell_envp *current;

	current = envp;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	add_envp(const char *key, const char *value, t_minishell_envp *envp)
{
	t_minishell_envp *current;

	current = envp;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return;
		}
		current = current->next;
	}
}

int cd(int fd, char **argv, t_minishell_envp *envp)
{
    char *home_path;
    char *old_path;
    char *new_path;

    if (count_argv(argv) > 2)
    {
        ft_dprintf(fd, "-minishel: cd: too many arguments\n");
        return (EXIT_FAILURE);
    }
    if (argv[1] == NULL)
    {
        home_path = minishell_getenv("HOME", envp);
        if (home_path == NULL)
        {
            ft_dprintf(fd, "cd: HOME not set\n");
            return (EXIT_FAILURE);
        }
        new_path = home_path;
    }
    else
        new_path = argv[1];
    old_path = getcwd(NULL, 0);
    if (chdir(new_path) == -1)
    {
        ft_dprintf(fd, "cd: %s: No such file or directory\n", new_path);
        return (EXIT_FAILURE);
    }
    new_path = getcwd(NULL, 0);
	// t_minishell_envp にPWD,PLDPWDを追加する必要がある
	add_envp("PWD", new_path, envp);
	add_envp("OLDPWD", old_path, envp);
    ft_printf("old_path: %s\n", old_path);
    ft_printf("new_path: %s\n", new_path);
    return (EXIT_SUCCESS);
}
