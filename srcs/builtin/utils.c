/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 09:03:16 by marvin            #+#    #+#             */
/*   Updated: 2025/05/01 09:03:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell/minishell.h>
# include <libft/std_string.h>
# include <libft/ft_string.h>
# include <stdlib.h>
# include <libft/ft_stdio.h>

void    add_double_quotes(int fd, t_string *str, const char *key, const char *value)
{
    ft_str_push_str(str, key);
    ft_str_push_str(str, "=\"");
    ft_str_push_str(str, value);
    ft_str_push_str(str, "\"\n");
    ft_dprintf(fd, "%s", str->str);
}
