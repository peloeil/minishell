/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:09:17 by sota              #+#    #+#             */
/*   Updated: 2024/10/03 03:26:16 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_list.h>

static void	*on_failure(t_list *res, void *new_content, void (*del)(void *))
{
	ft_list_clear(&res, del);
	if (del != NULL)
		del(new_content);
	return (NULL);
}

t_list	*ft_list_map(t_list *head, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*node;
	t_list	*cur;
	void	*new_content;

	if (head == NULL || f == NULL)
		return (NULL);
	res = NULL;
	cur = head;
	while (1)
	{
		new_content = f(cur->content);
		node = ft_list_new(new_content);
		if (node == NULL)
			return (on_failure(res, new_content, del));
		ft_list_push_back(&res, node);
		cur = cur->next;
		if (cur == head)
			break ;
	}
	return (res);
}
