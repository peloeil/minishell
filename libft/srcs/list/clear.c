/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:09:05 by sota              #+#    #+#             */
/*   Updated: 2024/10/03 02:19:35 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft/ft_list.h>

void	ft_list_clear(t_list **head, void (*del)(void *))
{
	t_list	*cur;
	t_list	*nxt;

	if (head == NULL)
		return ;
	if (*head == NULL)
		return ;
	cur = *head;
	while (1)
	{
		nxt = cur->next;
		if (del != NULL)
			del(cur->content);
		free(cur);
		cur = nxt;
		if (cur == *head)
			break ;
	}
	*head = NULL;
	return ;
}
