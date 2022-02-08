/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:36:01 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/08 15:33:29 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_boolean
// 	exec(t_mini *s)
// {
// 	t_command *cmd;

// 	cmd = s->cmd;
// 	while(cmd)
// 	{
// 		if (cmd->command && __is_builtins__(cmd))
// 			exec_builtins(s, cmd);
// 		cmd = cmd->next;
// 	}
// 	return (__SUCCESS);
// }