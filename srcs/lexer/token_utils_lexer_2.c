/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_lexer_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 11:53:20 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/23 12:11:36 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	__add_token_pip__(t_mini *s)
{
	add_token_back(&s->lexer, UNSET, PIP);
	s->prompt++;
}

void
	__add_token_r_right__(t_mini *s)
{
	if (s->prompt[1] == R_RIGHT)
	{
		add_token_back(&s->lexer, UNSET, DR_RIGHT);
		s->prompt += 2;
	}
	else
	{
		add_token_back(&s->lexer, UNSET, R_RIGHT);
		s->prompt += 1;
	}
}

void
	__add_token_r_left__(t_mini *s)
{
	if (s->prompt[1] == R_LEFT)
	{
		add_token_back(&s->lexer, UNSET, DR_LEFT);
		s->prompt += 2;
	}
	else
	{
		add_token_back(&s->lexer, UNSET, R_LEFT);
		s->prompt += 1;
	}
}

void
	__add_token_arg__(t_mini *s)
{
	uint64_t	size;
	char		*save;

	size = 0;
	save = s->prompt;
	add_token_back(&s->lexer, UNSET, ARGS);
	while (*s->prompt && __FALSE == __is_charset(*s->prompt,
			TOKEN_CS) && s->error != __TRUE)
	{
		if (*s->prompt == SINGLE_QUOTES)
			__skip_quote__(s, &size);
		else if (*s->prompt == DOUBLE_QUOTES)
			__skip_quotes__(s, &size);
		else
		{
			size++;
			s->prompt++;
		}
	}
	(find_last_elem(&s->lexer))->argument = __mstrldup(save,
		size, LEXER_STOCKAGE);
}
