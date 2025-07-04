/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:05:48 by marvin            #+#    #+#             */
/*   Updated: 2025/06/29 11:48:49 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/signal.h>
#include <minishell/execute.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>

volatile sig_atomic_t	g_received_signal = 0;

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
	if (save_signum(-1) == SIGINT)
	{
		update_exit_status(STATUS_SIG_BASE + SIGINT, envp);
		save_signum(0);
		g_received_signal = 0;
	}
}
