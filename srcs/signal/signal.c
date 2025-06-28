/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:05:48 by marvin            #+#    #+#             */
/*   Updated: 2025/06/28 21:15:37 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/signal.h>
#include <minishell/execute.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>

volatile sig_atomic_t	g_received_signal = 0;

int	heredoc_sig_hook(void)
{
	static int	flag = 0;

	if (flag && g_received_signal == 0)
		flag = 0;
	if (flag)
		return (1);
	if (g_received_signal == SIGINT)
	{
		flag = 1;
		rl_done = 1;
	}
	return (0);
}

int	sig_hook(void)
{
	static int	flag = 0;

	if (flag && g_received_signal == 0)
		flag = 0;
	if (flag)
		return (1);
	if (g_received_signal == SIGINT)
	{
		flag = 1;
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	return (0);
}

static void	sig_handler(int signo)
{
	g_received_signal = signo;
}

void	setup_signal_handler(void)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigemptyset(&sigint.sa_mask);
	sigint.sa_flags = 0;
	sigint.sa_handler = sig_handler;
	sigaction(SIGINT, &sigint, NULL);
	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_flags = 0;
	sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigquit, NULL);
}

void	signal_setup_after_readline(t_envp **envp)
{
	struct sigaction	sigquit;

	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_flags = 0;
	sigquit.sa_handler = sig_handler;
	sigaction(SIGQUIT, &sigquit, NULL);
	if (sig_hook() == 1)
	{
		update_exit_status(STATUS_SIG_BASE + g_received_signal, envp);
		g_received_signal = 0;
	}

}
