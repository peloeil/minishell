/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:09:20 by sota              #+#    #+#             */
/*   Updated: 2024/10/03 03:26:47 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_list.h>

size_t	ft_list_size(t_list *head)
{
	size_t	count;
	t_list	*cur;

	if (head == NULL)
		return (0);
	count = 0;
	cur = head;
	while (1)
	{
		count++;
		cur = cur->next;
		if (cur == head)
			break ;
	}
	return (count);
}
