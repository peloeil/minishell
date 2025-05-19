/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:56:03 by sota              #+#    #+#             */
/*   Updated: 2025/05/16 18:11:30 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <minishell/lexer.h>
# include <minishell/parser.h>
# include <libft/std_string.h>
# include <sys/stat.h>

# define PROMPT "minishell$ "
# define NUMERIC "numeric argument required"
# define TOO_MANY "-minishell: exit: too many arguments"

// ENVIRONMENT
# define FLAG_EXPORT 0b00000001
# define FLAG_VALUE 0b00000010
# define FLAG_UNSET 0b00000100
# define FLAG_SPECIAL 0b00001000
# define FLAG_HIDDEN 0b00010000

typedef struct s_envp
{
	char			*key;
	char			*value;
	int				exported;
	struct s_envp	*next;
}	t_envp;

// wrappers
char	*wrap_readline(const char *prompt);
int		wrap_close(int *fd, int afterfd);
int		wrap_dup2(int oldfd, int newfd);
int		wrap_fork(void);
int		wrap_open(const char *file, int flag);
int		wrap_stat(const char *path, struct stat *statbuf);
int		wrap_pipe(int *pipefd);
int		wrap_unlink(const char *path);

int		evaluate_command(const char *cmd, t_envp *ms_envp)
		__attribute__((nonnull(1, 2)));
int		set_command_path(char **const pathptr, const char *cmd, t_envp *envp)
		__attribute__((nonnull(2, 3)));
char	*ft_getenv(const char *key, const t_envp *envp)
		__attribute__((nonnull(1)));
int		ft_haskey(char *key, t_envp *envp)
		__attribute__((nonnull(1)));
int		make_ms_envp(t_envp **ms_envp, char **envp)
		__attribute__((nonnull(2)));

void	free_strs(char **strs)
		__attribute__((nonnull(1)));
void	free_ms_envp(t_envp *env);
void	free_token(void *ptr);
void	free_tokens(t_token_list *tokens);
void	free_ast(t_ast_node *ast);
int		found_parse_error(t_ast_node *ast)
		__attribute__((nonnull(1)));
int		error_return(const char *name, const char *msg)
		__attribute__((nonnull(1, 2)));

//builtin

void	make_str(int is_double, t_string *str, const char *key,
			const char *value);
int		echo(int fd, char **argv, t_envp **envp);
int		env(int fd, char **argv, t_envp **envp);
int		export(int fd, char **argv, t_envp **envp);
int		pwd(int fd, char **argv, t_envp **envp);
int		cd(int fd, char **argv, t_envp **envp);
int		unset(int fd, char **argv, t_envp **envp);
int		builtin_exit(int fd, char **argv, t_envp **envp);

// cd_utils
int		add_envp_with_flag(char *key, char *value, t_envp *envp, int flags);
int		update_env_value(const char *key, const char *value, t_envp *envp);
int		get_env_flags(const char *key, t_envp *envp);

// builtin/utils.c
t_envp	*create_new_node(char *key, char *value, int exported);
int		print_sorted_env(int fd, t_envp *envp);
void	add_double_quotes(int fd,
			t_string *str,
			const char *key,
			const char *value);
void	sort_envp(t_envp **head);
int		count_argv(char **argv);

#endif // MINISHELL_H
