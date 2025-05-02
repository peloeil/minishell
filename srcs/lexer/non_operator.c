/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:45:32 by sota              #+#    #+#             */
/*   Updated: 2025/05/02 17:05:45 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/lexer.h>
#include <libft/ft_string.h>
#include <libft/std_string.h>
#include <stdlib.h>

static int	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

static int	is_delimiter(const char *input, size_t index, int in_quote)
{
	char	c;

	c = input[index];
	if (c == '\0' || (!in_quote && is_blank(c)))
		return (1);
	if (!in_quote && identify_operator(input, index) != TOKEN)
		return (1);
	return (0);
}

static void	change_quote_state(int *in_quote, char c)
{
	if (*in_quote == 0)
		*in_quote = (int)c;
	else if (*in_quote == c)
		*in_quote = 0;
}

char	*read_string(const char *input, size_t index)
{
	t_string	str;
	int			in_quote;
	char		c;

	ft_str_new(&str);
	in_quote = 0;
	while (1)
	{
		if (is_delimiter(input, index, in_quote))
			break ;
		c = input[index];
		ft_str_push(&str, c);
		if (c == '\"' || c == '\'')
			change_quote_state(&in_quote, c);
		index++;
	}
	if (in_quote)
	{
		free(str.str);
		return (NULL);
	}
	return (str.str);
}
