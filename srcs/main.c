/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:49:27 by sota              #+#    #+#             */
/*   Updated: 2025/05/16 15:20:32 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/execute.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/history.h>

static int	initial_setup(t_envp **ms_envp, char **envp)
{
	if (make_ms_envp(ms_envp, envp) == -1)
		return (-1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_str;
	t_envp	*ms_envp;

	(void)argc;
	if (initial_setup(&ms_envp, envp) == -1)
		return (STATUS_ERRORS);
	while (1)
	{
		cmd_str = wrap_readline(PROMPT);
		if (cmd_str == NULL)
			break ;
		add_history(cmd_str);
		if (evaluate_command(cmd_str, ms_envp) == -1)
			update_exit_status(STATUS_ERRORS, ms_envp);
	}
	argv[1] = NULL;
	builtin_exit(STDOUT_FILENO, argv, &ms_envp);
}
