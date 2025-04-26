/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:56:03 by sota              #+#    #+#             */
/*   Updated: 2025/04/16 15:28:57 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell$ "

typedef struct minishell_envp
{
	char	*key;
	char	*value;
	int		exported;
	struct minishell_envp *next;
}	t_minishell_envp;

char	*wrap_readline(const char *prompt, const int is_interactive)
		__attribute__((nonnull(1)));
int		eval_cmd(const char *cmd, t_minishell_envp *minishell_envp, const char **envp)
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
int 	export(char *argv[], t_minishell_envp *envp);

#endif // MINISHELL_H
