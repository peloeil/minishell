/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:49:27 by sota              #+#    #+#             */
/*   Updated: 2025/06/27 22:19:28 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_stdio.h>
#include <libft/ft_stdlib.h>
#include <minishell/execute.h>
#include <minishell/minishell.h>
#include <minishell/signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>

static int	initial_setup(t_envp **ms_envp, char **envp)
{
	if (init_ms_envp(ms_envp, envp) == -1)
		return (-1);
	setup_signal_handler();
	rl_signal_event_hook = sig_hook;
	return (0);
}

static void	exit_shell(t_envp **ms_envp)
{
	int	status;

	status = ft_atoi(ft_getenv("?", *ms_envp));
	free_ms_envp(*ms_envp);
	exit(status);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_str;
	t_envp	*ms_envp;
	int		status;

	(void)argc;
	(void)argv;
	if (initial_setup(&ms_envp, envp) == -1)
		return (STATUS_ERRORS);
	while (1)
	{
		g_received_signal = 0;
		cmd_str = wrap_readline(PROMPT);
		if (cmd_str == NULL)
			break ;
		add_history(cmd_str);
		status = evaluate_command(cmd_str, &ms_envp);
		if (status == -2)
			break ;
		if (status == -1)
			update_exit_status(STATUS_MISUSE, &ms_envp);
	}
	exit_shell(&ms_envp);
}
