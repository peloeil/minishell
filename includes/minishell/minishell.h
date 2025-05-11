/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:56:03 by sota              #+#    #+#             */
/*   Updated: 2025/05/10 20:17:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <minishell/lexer.h>
# include <minishell/parser.h>
# include <libft/std_string.h>

# define PROMPT "minishell$ "
# define FLAG_EXPORT 0b00000001
# define FLAG_VALUE 0b00000010
# define FLAG_UNSET 0b00000100

typedef struct s_envp
{
	char			*key;
	char			*value;
	int				exported;
	struct s_envp	*next;
}	t_envp;

char	*wrap_readline(const char *prompt)
		__attribute__((nonnull(1)));
int		wrap_close(int *fd, int is_infd);
int		eval_cmd(const char *cmd, t_envp *ms_envp)
		__attribute__((nonnull(1, 2)));
int		set_cmd_path(char **const path_ptr, const char *cmd, const t_envp *envp)
		__attribute__((nonnull(3)));
char	*ft_getenv(const char *key, const t_envp *envp)
		__attribute__((nonnull(1)));
t_envp	*make_ms_envp(char **envp)
		__attribute__((nonnull(1)));

void	free_strs(char **strs)
		__attribute__((nonnull(1)));
void	free_ms_envp(t_envp *env)
		__attribute__((nonnull(1)));
void	free_tokens(t_token_list *tokens, int parse_failed)
		__attribute__((nonnull(1)));
void	free_ast(t_ast_node *ast, int status)
		__attribute__((nonnull(1)));
int		check_parse_error(t_ast_node *ast)
		__attribute__((nonnull(1)));

//builtin

void	make_str(int is_double, t_string *str, const char *key,
			const char *value);
int		pwd(void);
int		echo(int fd, char *argv[]);
int		export(int fd, char *argv[], t_envp *envp);
int		unset(char *argv[], t_envp **envp);
int		env(int fd, t_envp *envp);
int		cd(char *argv[], t_envp *envp);

// builtin/utils.c
t_envp	*create_new_node(char *key, char *value, int exported);
void	print_sorted_env(int fd, t_envp *envp);
void	add_double_quotes(int fd,
			t_string *str,
			const char *key,
			const char *value);
void	sort_envp(t_envp **head);
int		count_argv(char **argv);
#endif // MINISHELL_H
