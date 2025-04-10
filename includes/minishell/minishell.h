/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:56:03 by sota              #+#    #+#             */
/*   Updated: 2025/04/10 16:04:12 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell$ "

char	*wrap_readline(const char *prompt, const int is_interactive);
int		eval_cmd(const char *cmd, const char **envp)
		__attribute__((nonnull(1, 2)));
int		set_cmd_path(char **const path_ptr, const char *cmd, const char **envp);
void	free_strs(const char **strs);
char	*ft_getenv(const char *key, const char **envp)
		__attribute__((nonnull(1, 2)));

#endif // MINISHELL_H
