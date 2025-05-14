/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:49:27 by sota              #+#    #+#             */
/*   Updated: 2025/05/14 21:29:29 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <stdlib.h>
#include <stdio.h>
#include <libft/ft_stdio.h>
#include <libft/ft_string.h>

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_str;
	t_envp	*ms_envp;

	(void)argc;
	(void)argv;
	ms_envp = make_ms_envp(envp);
	while (1)
	{
		cmd_str = wrap_readline(PROMPT);
		if (cmd_str == NULL)
			break ;
		eval_cmd(cmd_str, ms_envp);
		free(cmd_str);
	}
	ft_printf("exit\n");
	free_ms_envp(ms_envp);
	return (EXIT_SUCCESS);
}
