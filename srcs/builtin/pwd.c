#include <minishell/minishell.h>
#include <stdlib.h>
#include <libft/ft_stdio.h>

int pwd(int argc, char *argv[])
{
    char	*cwd;

	if (argv[1])
	{
		printf("pwd: too many arguments\n");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	ft_printf("%s\n", cwd);
	free(cwd);
	return (0);
}
