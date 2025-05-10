/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:17:31 by sota              #+#    #+#             */
/*   Updated: 2025/05/10 17:35:43 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/lexer.h>
#include <stdlib.h>

static void	free_token(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	free(token->str);
	free(token);
}

void	free_tokens(t_token_list *tokens, int parse_failed)
{
	if (parse_failed)
		ft_list_clear(&tokens, free_token);
	else
		ft_list_clear(&tokens, free);
}
