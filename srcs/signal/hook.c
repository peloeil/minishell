/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:54:45 by sota              #+#    #+#             */
/*   Updated: 2025/06/28 20:58:31 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/signal.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>

int	heredoc_signal(int num)
{
	static int	signum = 0;

	if (num != -1)
		signum = num;
	return (signum);
}

int	heredoc_sig_hook(void)
{
	static int	flag = 0;

	if (flag && g_received_signal == 0)
		flag = 0;
	if (flag)
		return (1);
	if (g_received_signal == SIGINT)
	{
		heredoc_signal(SIGINT);
		flag = 1;
		rl_done = 1;
	}
	return (0);
}

int	save_signum(int num)
{
	static volatile sig_atomic_t	signum = 0;

	if (num != -1)
		signum = num;
	return (signum);
}

int	sig_hook(void)
{
	if (g_received_signal == SIGINT)
		save_signum(SIGINT);
	if (save_signum(-1) == SIGINT && g_received_signal == 0)
		return (SIGINT);
	if (g_received_signal == SIGINT)
	{
		g_received_signal = 0;
		rl_replace_line("", 0);
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		return (SIGINT);
	}
	return (save_signum(-1));
}
