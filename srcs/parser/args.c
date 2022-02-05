/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:56:25 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/05 17:56:41 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	cmd_parsing(t_command *cmd, t_lexer **lexer)
{
	if (cmd->command == NULL)
	{
		cmd->command = __strdup((*lexer)->argument);
		__strs_add_back(&cmd->args, __strdup((*lexer)->argument));
	}
	else
		__strs_add_back(&cmd->args, __strdup((*lexer)->argument));
	(*lexer) = (*lexer)->next;
}
