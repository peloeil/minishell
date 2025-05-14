/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_strs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:59:03 by sota              #+#    #+#             */
/*   Updated: 2025/05/14 19:04:32 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_strs(char **strs)
{
	size_t	i;

	i = 0;
	if (strs == NULL)
		return ;
	while (strs[i] != NULL)
		free((void *)strs[i++]);
	free((void *)strs);
}
