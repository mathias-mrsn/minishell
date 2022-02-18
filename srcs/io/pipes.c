/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <malouvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:01:36 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/15 17:06:17 by malouvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(t_command *cmd)
{
	if (cmd->type == PIP)
	{
		if (pipe(cmd->tube) < 0)
			return (0);
		else
			return (1);
	}
	return (1);
}

void	close_prev_pipe(t_command *cmd)
{
	if (cmd->prev && cmd->prev->type == PIP)
	{
		close(cmd->prev->tube[0]);
		close(cmd->prev->tube[1]);
	}
}
