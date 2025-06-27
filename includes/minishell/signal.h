/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:05:16 by marvin            #+#    #+#             */
/*   Updated: 2025/06/27 21:56:43 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include <signal.h>

extern volatile sig_atomic_t	g_received_signal;

void							setup_signal_handler(void);
void							setup_heredoc_signal(void);
int								heredoc_sig_hook(void);
int								sig_hook(void);

#endif
