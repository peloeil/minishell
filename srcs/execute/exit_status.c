/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 01:03:28 by sota              #+#    #+#             */
/*   Updated: 2025/05/30 19:31:35 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/execute.h>
#include <minishell/minishell.h>
#include <libft/ft_stdio.h>

int	update_exit_status(t_exit_status status, t_envp **envp)
{
	char	str[20];

	if (ft_snprintf(str, sizeof(str), "?=%d", (int)status) < 0)
		return (-1);
	return (update_ms_envp(envp, str, FLAG_SPECIAL));
}
