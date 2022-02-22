/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:55:18 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/22 17:58:38 by mamaurai         ###   ########.fr       */
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

void
	__env_option_error__(char *str)
{
	__putstr("minishell: export: `", STDERR_FILENO);
	__putstr(str, STDERR_FILENO);
	__putstr("': invalid option\n", STDERR_FILENO);
}

void
	__env_error_value__(char *str)
{
	__putstr("minishell: export: `", STDERR_FILENO);
	__putstr(str, STDERR_FILENO);
	__putstr("': not a valid identifier\n", STDERR_FILENO);
}
