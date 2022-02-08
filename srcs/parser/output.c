/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:55:43 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/08 15:59:49 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_boolean
	set_simple_right(t_mini *s, t_command *cmd, t_lexer **lexer)
{
	int 		fd;

	fd = open((*lexer)->next->argument, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (-1 == fd)
	{
		strerror(errno);
		s->error = __TRUE;
		return (__FAILURE);
	}
	if (cmd->outfile != 0)
		close(cmd->outfile);
	cmd->outfile = fd;
	return (__SUCCESS);
}

static t_boolean
	set_double_right(t_mini *s, t_command *cmd, t_lexer **lexer)
{
	int 		fd;

	fd = open((*lexer)->next->argument, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (-1 == fd)
	{
		strerror(errno);
		s->error = __TRUE;
		return (__FAILURE);
	}
	if (cmd->outfile != 0)
		close(cmd->outfile);
	cmd->outfile = fd;
	return (__SUCCESS);
}

void
	output_parsing(t_mini *s, t_command *cmd, t_lexer **lexer)
{
	if ((*lexer)->token == R_RIGHT)
		set_simple_right(s, cmd, lexer);
	if ((*lexer)->token == DR_RIGHT)
		set_double_right(s, cmd, lexer);
	(*lexer) = (*lexer)->next->next;
}