#include <minishell/minishell.h>
#include <stdlib.h>
#include <libft/ft_stdio.h>

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
