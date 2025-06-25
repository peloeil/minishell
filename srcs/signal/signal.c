/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:05:48 by marvin            #+#    #+#             */
/*   Updated: 2025/06/11 18:10:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include <stdio.h>
#include <termios.h>
#include <minishell/signal.h>
#include <unistd.h>

volatile sig_atomic_t	g_received_signal = 0;

static void	set_echoctl(int enable)
{
    struct termios term;

    if (tcgetattr(STDIN_FILENO, &term) == 0)
    {
        if (enable)
            term.c_lflag |= ECHOCTL;
        else
            term.c_lflag &= ~ECHOCTL;
        tcsetattr(STDIN_FILENO, TCSANOW, &term);
    }
}

static void	sig_handler(int signo)
{
    g_received_signal = signo;
    if (signo == SIGINT)
    {
        set_echoctl(1);
	rl_done = 1;
        rl_replace_line("", 0);
        write(1, "\n", 1);
        rl_on_new_line();
	rl_redisplay();
    }
    else if (signo == SIGQUIT)
    {
        set_echoctl(0);
	rl_done = 1;
	rl_redisplay();
    }
}

void	setup_signal(void)
{
    struct sigaction	act;

    set_echoctl(1);
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = sig_handler;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);
}

void	handle_signal_in_main(void)
{
    if (g_received_signal == SIGINT
	|| g_received_signal == SIGQUIT)
        g_received_signal = 0;
}
