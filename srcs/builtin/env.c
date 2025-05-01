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
	while (envp != NULL)
	{
		add_double_quotes(fd, &str, envp->key, envp->value);
		envp = envp->next;
	}
	ft_dprintf(fd, "%s", str.str);
	return (0);
}
