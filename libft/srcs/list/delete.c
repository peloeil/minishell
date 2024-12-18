/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:09:07 by sota              #+#    #+#             */
/*   Updated: 2024/10/03 02:57:35 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft/ft_list.h>

void	ft_list_delete(t_list *node, void (*del)(void *))
{
	if (node == NULL)
		return ;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	if (del != NULL)
		del(node->content);
	free(node);
	return ;
}
