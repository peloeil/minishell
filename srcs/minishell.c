#include <minishell/ms_consts.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <libft/ft_stdio.h>

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline(PROMPT);
		if (input == NULL)
			break ;
		ft_printf("input: %s\n", input);
		free(input);
	}
	return (EXIT_SUCCESS);
}
