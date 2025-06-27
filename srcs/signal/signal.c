/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:05:48 by marvin            #+#    #+#             */
/*   Updated: 2025/06/27 16:42:07 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/signal.h>
#include <signal.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t	g_received_signal = 0;

static void	sig_handler(int signo)
{
    g_received_signal = signo;
    if (signo == SIGINT && RL_ISSTATE(RL_STATE_READCMD))
    {
        rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
	rl_redisplay();
    }
}

void	setup_signal(void)
{
    struct sigaction	sigint;
    struct sigaction	sigquit;

    sigemptyset(&sigint.sa_mask);
    sigint.sa_flags = SA_RESTART;
    sigint.sa_handler = sig_handler;
    sigaction(SIGINT, &sigint, NULL);
    sigemptyset(&sigquit.sa_mask);
    sigquit.sa_flags = SA_RESTART;
    sigquit.sa_handler = sig_handler;
    sigaction(SIGQUIT, &sigquit, NULL);
}
