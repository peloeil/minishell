#include <minishell/ms_consts.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include <libft/ft_stdio.h>

static char	*xreadline(const char *prompt, int is_interactive)
{
	int		saved_stdout;
	int		saved_stderr;
	int		dev_null;
	char	*res;

	if (is_interactive)
		return (readline(prompt));
	saved_stdout = dup(STDOUT_FILENO);
	saved_stderr = dup(STDERR_FILENO);
	dev_null = open("/dev/null", O_WRONLY);
	dup2(dev_null, STDOUT_FILENO);
	dup2(dev_null, STDERR_FILENO);
	close(dev_null);
	res = readline(NULL);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stderr, STDERR_FILENO);
	close(saved_stdout);
	close(saved_stderr);
	return (res);
}

int	main(void)
{
	char	*input;

	while (1)
	{
		input = xreadline(PROMPT, isatty(STDIN_FILENO) && isatty(STDERR_FILENO));
		if (input == NULL)
			break ;
		ft_printf("%s\n", input);
		free(input);
	}
	return (EXIT_SUCCESS);
}
