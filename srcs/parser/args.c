/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:56:25 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/17 13:45:05 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	cmd_parsing(t_command *cmd, t_lexer **lexer)
{
	if (cmd->command == NULL)
	{
		cmd->command = __mstrdup((*lexer)->argument, COMMAND_STOCKAGE);
		__mstrs_add_back(&cmd->args, __mstrdup((*lexer)->argument,
				COMMAND_STOCKAGE), COMMAND_STOCKAGE);
	}
	else
	{
		if (__str_count((*lexer)->argument, '*'))
			wildcard(s(), cmd, (*lexer)->argument);
		else
			__mstrs_add_back(&cmd->args, __mstrdup((*lexer)->argument,
					COMMAND_STOCKAGE), COMMAND_STOCKAGE);
	}
	(*lexer) = (*lexer)->next;
}
