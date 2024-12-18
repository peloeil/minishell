/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_front.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 03:41:56 by sota              #+#    #+#             */
/*   Updated: 2024/12/13 17:53:08 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_list.h>

t_list	*ft_list_pop_front(t_list **head)
{
	t_list	*res;

	if (*head == NULL)
		return (NULL);
	res = *head;
	if (res->next == res)
	{
		*head = NULL;
		return (res);
	}
	(*head)->prev->next = (*head)->next;
	(*head)->next->prev = (*head)->prev;
	*head = (*head)->next;
	res->prev = res;
	res->next = res;
	return (res);
}
