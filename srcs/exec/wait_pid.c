/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:45:40 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/22 17:46:37 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_child(pid_t child)
{
	int	status;

	status = 0;
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		s()->g_exit_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status) && WCOREDUMP(status))
	{
		__putstr("Quit (core dumped)\n", 2);
		s()->g_exit_code = 131;
	}
	s()->prog_state = 0;
}
