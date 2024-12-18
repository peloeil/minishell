/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:09:11 by sota              #+#    #+#             */
/*   Updated: 2024/12/18 00:23:52 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_list.h>

void	ft_list_iter(t_list *head, void (*f)(void *))
{
	t_list	*cur;

	if (head == NULL || f == NULL)
		return ;
	cur = head;
	while (1)
	{
		f(head->content);
		cur = cur->next;
		if (cur == head)
			break ;
	}
	return ;
}
