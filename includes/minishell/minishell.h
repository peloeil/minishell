/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:56:03 by sota              #+#    #+#             */
/*   Updated: 2025/04/27 17:45:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell$ "

char	*wrap_readline(const char *prompt, const int is_interactive)
		__attribute__((nonnull(1)));
int		eval_cmd(const char *cmd, const char **envp)
		__attribute__((nonnull(1, 2)));
int		set_cmd_path(char **const path_ptr, const char *cmd, const char **envp)
		__attribute__((nonnull(3)));
void	free_strs(const char **strs)
		__attribute__((nonnull(1)));
char	*ft_getenv(const char *key, const char **envp)
		__attribute__((nonnull(1, 2)));

//builtin
int		pwd(void);
int		echo(int argc, char *argv[]);
int		env(const char **envp);

#endif // MINISHELL_H
