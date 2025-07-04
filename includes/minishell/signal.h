/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:05:16 by marvin            #+#    #+#             */
/*   Updated: 2025/06/28 21:16:04 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include <minishell/execute.h>
# include <signal.h>

extern volatile sig_atomic_t	g_received_signal;

void							setup_signal_handler(void);
void							signal_setup_after_readline(t_envp **envp);
int								heredoc_sig_hook(void);
int								sig_hook(void);
int								heredoc_signal(int num);
int								save_signum(int num);

#endif
