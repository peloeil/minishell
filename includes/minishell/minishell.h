/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:56:03 by sota              #+#    #+#             */
/*   Updated: 2025/03/11 18:26:50 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell$ "

char	*wrap_readline(const char *prompt, const int is_interactive);
int		eval_cmd(const char *cmd, const char **envp)
		__attribute__((__nonnull__(1)));

#endif // MINISHELL_H
