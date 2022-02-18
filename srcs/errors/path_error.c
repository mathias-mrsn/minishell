/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <malouvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:55:18 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/17 20:17:36 by malouvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	path_not_set(t_command *cmd)
{
	if (access(cmd->command, 0) == 0)
		__execve__(cmd->command, cmd->args);
	write(2, "minishell:  no such file or directory: ", 39);
	write(2, cmd->command, __strlen(cmd->command));
	write(2, "\n", 1);
	exit (127);
}
