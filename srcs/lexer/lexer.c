/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:38:59 by sota              #+#    #+#             */
/*   Updated: 2025/05/15 01:44:44 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
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

	*tokens = NULL;
	idx = 0;
	while (1)
	{
		tkn = (t_token *)malloc(sizeof(t_token));
		cur = ft_list_new(tkn);
		if (tkn == NULL || cur == NULL || set_next_token(tkn, cmd, &idx) == -1)
		{
			free_token(tkn);
			free_tokens(*tokens);
			free(cur);
			return (-1);
		}
		if (tkn->str == NULL)
		{
			free(tkn);
			break ;
		}
		ft_list_push_back(tokens, cur);
	}
	return (0);
}
