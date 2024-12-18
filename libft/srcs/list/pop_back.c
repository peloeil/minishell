/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_back.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 03:27:16 by sota              #+#    #+#             */
/*   Updated: 2024/12/13 17:53:21 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_list.h>

t_list	*ft_list_pop_back(t_list **head)
{
	t_list	*res;

	if (*head == NULL)
		return (NULL);
	res = (*head)->prev;
	if (res == *head)
	{
		*head = NULL;
		return (res);
	}
	(*head)->prev->prev->next = *head;
	(*head)->prev = (*head)->prev->prev;
	res->prev = res;
	res->next = res;
	return (res);
}
