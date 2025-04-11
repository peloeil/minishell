#include <minishell/minishell.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libft/ft_stdio.h>

int pwd(void)
{
    char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd");
		return (1);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	return (0);
}
