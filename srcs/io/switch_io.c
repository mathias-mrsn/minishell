/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <malouvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:02:19 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/15 17:06:13 by malouvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	switch_io(t_command *cmd)
{	
	if (cmd->prev && cmd->prev->type == PIP)
	{
		dup2(cmd->prev->tube[0], 0);
		close(cmd->prev->tube[1]);
	}
	if (cmd->type == PIP)
	{
		dup2(cmd->tube[1], 1);
		close(cmd->tube[0]);
	}
	if (cmd->outfile)
	{
		dup2(cmd->outfile, 1);
	}
	if (cmd->infile)
		dup2(cmd->infile, 0);
}
