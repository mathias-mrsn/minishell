/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:45:40 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/24 10:27:27 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_child(void)
{
	int			status;
	t_command	*cmd;

	cmd = s()->cmd;
	status = 0;
	while (cmd)
	{
		if (cmd->child)
		{
			waitpid(cmd->child, &status, 0);
			if (WIFEXITED(status))
				s()->g_exit_code = WEXITSTATUS(status);
			if (WIFSIGNALED(status) && WCOREDUMP(status))
			{
				__putstr("Quit (core dumped)\n", 2);
				s()->g_exit_code = 131;
			}
		}
		status = 0;
		cmd = cmd->next;
	}
}
