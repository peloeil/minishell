/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:17:31 by sota              #+#    #+#             */
/*   Updated: 2025/05/15 01:08:00 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/lexer.h>
#include <stdlib.h>

void	free_token(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	if (token == NULL)
		return ;
	free(token->str);
	free(token);
}

void	free_tokens(t_token_list *tokens)
{
	ft_list_clear(&tokens, free_token);
}
