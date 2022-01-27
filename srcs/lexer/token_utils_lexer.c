/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_lexer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:19:48 by mamaurai          #+#    #+#             */
/*   Updated: 2022/01/26 11:19:49 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	__skip_white_space__(t_mini *s)
{
	while (*s->prompt && __isempty(*s->prompt))
		s->prompt++;
}

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
	while (*s->prompt && __FALSE == __is_charset(*s->prompt, TOKEN_CS))
	{
		size++;
		s->prompt++;
	}
	find_last_elem(&s->lexer)->argument = __strldup(save, size);
}