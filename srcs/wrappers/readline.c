#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <fcntl.h>

char	*xreadline(const char *prompt, const int is_interactive)
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
