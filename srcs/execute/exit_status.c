/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 01:03:28 by sota              #+#    #+#             */
/*   Updated: 2025/05/15 04:05:01 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_stdio.h>
#include <libft/ft_stdlib.h>
#include <minishell/execute.h>
#include <minishell/minishell.h>

int	update_exit_status(t_exit_status status, t_envp *envp)
{
	char	*str_status;

	str_status = ft_itoa(status);
	return (add_with_flag("?", str_status, envp, FLAG_SPECIAL));
}
