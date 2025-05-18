/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:38:59 by sota              #+#    #+#             */
/*   Updated: 2025/05/15 15:42:33 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/lexer.h>
#include <libft/ft_string.h>
#include <libft/ft_stdlib.h>
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
		token->str = read_string(input, *index);
	if (token->str == NULL)
		return (-1);
	*index += ft_strlen(token->str);
	return (0);
}

int	tokenize_input(t_token_list **tokens, const char *cmd)
{
	size_t			idx;
	t_token			*tkn;
	t_token_list	*cur;
	int				failed;

	*tokens = NULL;
	idx = 0;
	while (1)
	{
		tkn = (t_token *)ft_calloc(1, sizeof(t_token));
		cur = ft_list_new(tkn);
		failed = (tkn == NULL || cur == NULL
				|| set_next_token(tkn, cmd, &idx) == -1);
		if (failed || tkn->str == NULL)
		{
			free_token(tkn);
			free(cur);
			if (!failed)
				break ;
			free_tokens(*tokens);
			return (-1);
		}
		ft_list_push_back(tokens, cur);
	}
	return (0);
}
