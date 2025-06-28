/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:05:48 by marvin            #+#    #+#             */
/*   Updated: 2025/06/27 22:23:59 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/signal.h>
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
	if (g_received_signal == SIGINT)
	{
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_received_signal = 0;
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

void	sigquit_handler_to_default(void)
{
	struct sigaction	sigquit;

	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_flags = 0;
	sigquit.sa_handler = sig_handler;
	sigaction(SIGQUIT, &sigquit, NULL);
}
