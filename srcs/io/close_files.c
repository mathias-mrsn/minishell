/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <malouvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:03:32 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/15 17:06:19 by malouvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_open_files(int stdin_copy, int stdout_copy)
{
	t_command	*cmd;

	cmd = s()->cmd;
	while (cmd)
	{
		if (cmd->infile)
			close(cmd->infile);
		if (cmd->outfile)
			close(cmd->outfile);
		unlink(".heredoc_tmp");
		cmd = cmd->next;
	}
	dup2(stdin_copy, 0);
	close(stdin_copy);
	dup2(stdout_copy, 1);
	close(stdout_copy);
}
