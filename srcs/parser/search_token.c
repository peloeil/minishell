/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:40:42 by sota              #+#    #+#             */
/*   Updated: 2025/05/15 00:59:43 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/lexer.h>

t_token_list	*search_token_from_left(
					t_token_id id,
					t_token_list *start,
					t_token_list *end)
{
	t_token_list	*cur;

	cur = start;
	while (1)
	{
		if (((t_token *)cur->content)->id == id)
			return (cur);
		if (cur == end)
			break ;
		cur = cur->next;
	}
	return (NULL);
}

t_token_list	*search_token_from_right(
					t_token_id id,
					t_token_list *start,
					t_token_list *end)
{
	t_token_list	*cur;

	cur = end;
	while (1)
	{
		if (((t_token *)cur->content)->id == id)
			return (cur);
		if (cur == start)
			break ;
		cur = cur->prev;
	}
	return (NULL);
}

t_token_list	*search_redirect_token(
						t_token_list *start,
						t_token_list *end)
{
	t_token_list	*cur;
	t_token_id		id;

	cur = start;
	while (1)
	{
		id = ((t_token *)cur->content)->id;
		if (id == LESS
			|| id == GREAT
			|| id == DLESS
			|| id == DGREAT
			|| id == LESSAND
			|| id == GREATAND)
			return (cur);
		if (cur == end)
			break ;
		cur = cur->next;
	}
	return (NULL);
}
