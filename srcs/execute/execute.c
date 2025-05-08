/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 00:03:53 by sota              #+#    #+#             */
/*   Updated: 2025/05/08 21:26:44 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/parser.h>
#include <minishell/execute.h>
#include <libft/ft_string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

static int	set_redirect_fd(t_token_id id, t_ast_node *file, int *fds)
{
	int	fd;

	if (id == LESS || id == LESSAND)
	{
		fd = open(file->args->content, O_RDONLY);
		if (fd == -1)
			return (-1);
		if (fds[READ_FD] != STDIN_FILENO)
			close(fds[READ_FD]);
		fds[READ_FD] = fd;
		return (0);
	}
	if (id == GREAT || id == GREATAND)
		fd = open(file->args->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (id == DGREAT)
		fd = open(file->args->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	if (fds[WRITE_FD] != STDOUT_FILENO)
		close(fds[WRITE_FD]);
	fds[WRITE_FD] = fd;
	return (0);
}

static int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	return (0);
}

static int	execute_builtin(t_arg_list *args, int in_fd, int out_fd, t_envp *ms_envp)
{
	char	**argv;
	char	**envp;

	(void)in_fd;
	if (make_argv(&argv, args, ms_envp) == -1)
		return (-1);
	if (make_envp(&envp, ms_envp) == -1)
	{
		free_strs(argv);
		return (-1);
	}
	if (ft_strcmp(args->content, "pwd") == 0)
		return (pwd());
	if (ft_strcmp(args->content, "echo") == 0)
		return (echo(out_fd, args->content));
	if (ft_strcmp(args->content, "export") == 0)
		return (export(out_fd, args->next->content, ms_envp));
	if (ft_strcmp(args->content, "env") == 0)
		return (env(out_fd, ms_envp));
	return (-1);
}

static int	execute_command(
				t_arg_list *args,
				int in_fd,
				int out_fd,
				t_envp *envp)
{
	pid_t	pid;

	if (is_builtin(args->content))
		return (execute_builtin(args->content, in_fd, out_fd, envp));
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		return (child_process(args, in_fd, out_fd, envp));
	return (parent_process(pid, in_fd, out_fd));
}

static int	execute_nopipe(t_ast_node *ast, int *fds, t_envp *envp)
{
	if (ast->id == COMMAND)
		return (execute_command(ast->args, fds[READ_FD], fds[WRITE_FD], envp));
	if (set_redirect_fd(ast->id, ast->left, fds) == -1)
		return (-1);
	return (execute_nopipe(ast->right, fds, envp));
}

static int	execute_pipe(t_ast_node *ast, int *fds, t_envp *envp)
{
	int	pipefds[2];

	if (pipe(pipefds) == -1)
		return (-1);
	fds[WRITE_FD] = pipefds[WRITE_FD];
	execute_nopipe(ast->left, fds, envp);
	fds[READ_FD] = pipefds[READ_FD];
	return (execute_ast(ast->right, fds, envp));
}

int	execute_ast(t_ast_node *ast, int *fds, t_envp *envp)
{
	if (ast->id == PIPE)
		return (execute_pipe(ast, fds, envp));
	return (execute_nopipe(ast, fds, envp));
}
