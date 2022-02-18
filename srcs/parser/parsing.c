/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:43:00 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/17 13:45:35 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean
	__next_is_pip__(t_lexer *tmp)
{
	while (tmp)
	{
		if (tmp->token == PIP)
			return (__TRUE);
		tmp = tmp->next;
	}
	return (__FALSE);
}

void
	cmd_parsing_hub(t_mini *s)
{
	t_lexer		*tmp;
	t_command	*cmd;

	tmp = s->lexer;
	cmd = add_command_front(&s->cmd);
	while (tmp && s->error != __TRUE)
	{
		if (__next_is_pip__(tmp) == __TRUE)
			cmd->type = PIP;
		if (tmp->token == ARGS)
			cmd_parsing(cmd, &tmp);
		else if (tmp->token == R_LEFT || tmp->token == DR_LEFT)
			input_parsing(s, cmd, &tmp);
		else if (tmp->token == R_RIGHT || tmp->token == DR_RIGHT)
			output_parsing(s, cmd, &tmp);
		else if (tmp->token == PIP)
		{
			cmd = add_command_back(&s->cmd);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}

t_boolean
	parsing(t_mini *s)
{
	if (NULL == s->lexer || s->error == __TRUE)
		return (__FAILURE);
	cmd_parsing_hub(s);
	return (__SUCCESS);
}
