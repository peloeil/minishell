/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:49:27 by sota              #+#    #+#             */
/*   Updated: 2025/03/11 18:27:22 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <stdlib.h>
#include <stdio.h>
#include <libft/ft_string.h>
#include <libft/ft_stdio.h>

t_minishell_envp	*make_minishell_envp(const char **envp)
{
	t_minishell_envp	*minishell_envp;
	t_minishell_envp	*head;
	char				*delimiter_pos;
	int					i;

	minishell_envp = NULL;
	head = NULL;
	i = 0;
	while (envp[i])
	{
		minishell_envp = malloc(sizeof(t_minishell_envp));
		if (!minishell_envp)
			return (NULL);
		delimiter_pos = ft_strchr(envp[i], '=');
		minishell_envp->key = ft_substr(envp[i], 0, delimiter_pos - envp[i]);
		minishell_envp->value = ft_strdup(delimiter_pos + 1);
		minishell_envp->exported = 1;
		minishell_envp->next = head;
		head = minishell_envp;
		i++;
	}
	return (head);
}

int	main(int argc, char **argv, char **envp)
{
	char				*cmd_str;
	t_minishell_envp	*minishell_envp;

	(void)argc;
	(void)argv;
	minishell_envp = make_minishell_envp((const char **)envp);
	while (1)
	{
		cmd_str = wrap_readline(
				PROMPT, isatty(STDIN_FILENO) && isatty(STDERR_FILENO)
				);
		if (cmd_str == NULL)
			break ;
		eval_cmd(cmd_str, minishell_envp, (const char **)envp);
		free(cmd_str);
	}
	return (EXIT_SUCCESS);
}
