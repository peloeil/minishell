/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:49:27 by sota              #+#    #+#             */
/*   Updated: 2025/03/11 17:58:03 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <stdlib.h>
#include <libft/ft_stdio.h>

int	main(void)
{
	char	*input;

	while (1)
	{
		input = wrap_readline(
				PROMPT, isatty(STDIN_FILENO) && isatty(STDERR_FILENO)
				);
		if (input == NULL)
			break ;
		ft_printf("%s\n", input);
		free(input);
	}
	return (EXIT_SUCCESS);
}
