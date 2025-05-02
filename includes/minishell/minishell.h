/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:56:03 by sota              #+#    #+#             */
/*   Updated: 2025/05/02 22:48:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft/std_string.h>

# define PROMPT "minishell$ "

typedef struct minishell_envp
{
	char					*key;
	char					*value;
	int						exported;
	struct minishell_envp	*next;
}	t_envp;

char	*wrap_readline(const char *prompt, const int is_interactive)
		__attribute__((nonnull(1)));
int		eval_cmd(
			int fd,
			const char *cmd,
			t_envp *minishell_envp,
			const char **envp)
		__attribute__((nonnull(2, 3)));
int		set_cmd_path(char **const path_ptr, const char *cmd, const char **envp)
		__attribute__((nonnull(3)));
void	free_strs(const char **strs)
		__attribute__((nonnull(1)));
char	*ft_getenv(const char *key, const char **envp)
		__attribute__((nonnull(1, 2)));

//builtin

void	make_str(int is_double, t_string *str, const char *key, const char *value);
int		pwd(void);
int		echo(int argc, char *argv[]);
int		export(int fd, char *argv[], t_envp *envp);
int		env(int fd, t_envp *envp);

// builtin/utils.c
void	print_sorted_env(int fd, t_envp *envp);
void	add_double_quotes(int fd,
			t_string *str,
			const char *key,
			const char *value);
void	sort_envp(t_envp **head);
#endif // MINISHELL_H
