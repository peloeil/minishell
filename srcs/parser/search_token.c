/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:40:42 by sota              #+#    #+#             */
/*   Updated: 2025/05/02 16:40:52 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/lexer.h>

t_list	*search_token_from_left(t_token_id id, t_list *start, t_list *end)
{
	t_list	*cur;

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

t_list	*search_token_from_right(t_token_id id, t_list *start, t_list *end)
{
	t_list	*cur;

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
