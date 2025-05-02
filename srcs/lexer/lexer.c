/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:38:59 by sota              #+#    #+#             */
/*   Updated: 2025/05/02 16:39:16 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/lexer.h>
#include <libft/ft_string.h>
#include <libft/ft_list.h>
#include <libft/ft_stdio.h>
#include <stdlib.h>

static int	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

int	set_next_token(t_token *token, const char *input, size_t *index)
{
	token->id = TOKEN;
	token->str = NULL;
	while (input[*index] != '\0' && is_blank(input[*index]))
		(*index)++;
	if (input[*index] == '\0')
		return (0);
	if (identify_operator(input, *index) != TOKEN)
	{
		token->id = identify_operator(input, *index);
		token->str = read_operator(input, *index);
	}
	else
	{
		token->str = read_string(input, *index);
		if (token->str == NULL)
			return (-1);
	}
	*index += ft_strlen(token->str);
	return (0);
}

t_list	*tokenize_input(const char *input)
{
	size_t		index;
	t_token		*token;
	t_list		*tokens;

	tokens = NULL;
	index = 0;
	while (1)
	{
		token = (t_token *)malloc(sizeof(t_token));
		if (set_next_token(token, input, &index) == -1)
		{
			ft_printf("syntax error\n");
			exit(EXIT_FAILURE);
		}
		if (token->str == NULL)
		{
			free(token);
			break ;
		}
		ft_list_push_back(&tokens, ft_list_new(token));
	}
	return (tokens);
}
