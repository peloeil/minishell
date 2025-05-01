/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:38:56 by marvin            #+#    #+#             */
/*   Updated: 2025/04/30 11:38:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell/minishell.h>
# include <libft/ft_string.h>
# include <libft/ft_stdio.h>
# include <libft/ft_put_fd.h>
# include <libft/std_string.h>
# include <stdlib.h>

int env(int fd, char **argv, t_minishell_envp *envp)
{
    t_string	str;

	if (ft_str_new(&str) == -1)
		return (1);
	if (argv[1] != NULL) {
		ft_dprintf(fd, "env: '%s': No such file or directory\n", argv[1]);
		return (1);
	}
	while (envp != NULL)
	{
		ft_str_push_str(&str, envp->key);
		ft_str_push_str(&str, " = \"");
		ft_str_push_str(&str, envp->value);
		ft_str_push_str(&str, "\"\n");
		envp = envp->next;
	}	
	ft_dprintf(fd, "%s", str.str);
	return (0);
}
