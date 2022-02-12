/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:54:52 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/12 11:36:18 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean
	set_simple_left(t_mini *s, t_command *cmd, t_lexer **lexer)
{
	int	fd;

	if (__FALSE == __file_exist((*lexer)->next->argument))
		return (__file_dont_exist__(s, (*lexer)->next->argument), __FAILURE);
	fd = open((*lexer)->next->argument, O_RDONLY);
	if (-1 == fd)
		return (__FAILURE);
	if (cmd->infile != 0)
		close(cmd->infile);
	cmd->infile = fd;
	return (__SUCCESS);
}

void
	input_parsing(t_mini *s, t_command *cmd, t_lexer **lexer)
{
	if ((*lexer)->token == R_LEFT)
		set_simple_left(s, cmd, lexer);
	else if ((*lexer)->token == DR_LEFT)
		set_here_doc(s, cmd, lexer);
	(*lexer) = (*lexer)->next->next;
}
