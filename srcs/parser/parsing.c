/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:43:00 by mamaurai          #+#    #+#             */
/*   Updated: 2022/01/25 17:15:31 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// void
// 	heredoc(t_command *cmd, t_lexer *lexer, t_mini *s)
// {
	
// }

void
	cmd_parsing(t_command *cmd, t_lexer *lexer)
{
	// if (cmd->command == NULL)
	// {
	// 	cmd->command = __strdup(lexer->argument);
	// 	lexer = lexer->next;
	// }
	// else
	__strs_add_front(&cmd->args, __strdup(lexer->argument));
	printf("%s\n", (cmd->args)[0]);
}

void
	cmd_parsing_hub(t_mini *s)
{
	t_lexer 	*tmp;

	tmp = s->lexer;
	s->cmd = add_command_back(&s->cmd);

	// if (tmp->token == DR_LEFT)
	// 	heredoc(cmd, tmp, s);
	if (tmp->token == ARGS)
		cmd_parsing(s->cmd, s->lexer);
	
	
}

t_boolean
	parsing(t_mini *s)
{
	if (NULL == s->lexer)
		return (__SUCCESS);
	cmd_parsing_hub(s);	
	return (__SUCCESS);
}