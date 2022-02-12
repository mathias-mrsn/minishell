/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_lexer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:19:48 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/12 11:55:11 by mamaurai         ###   ########.fr       */
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
	__skip_quote__(t_mini *s, uint64_t *size)
{
	(*size)++;
	s->prompt++;
	while (*s->prompt && *s->prompt != SINGLE_QUOTES)
	{
		(*size)++;
		s->prompt++;
	}
	(*size)++;
	s->prompt++;
}

void
	__skip_quotes__(t_mini *s, uint64_t *size)
{
	(*size)++;
	s->prompt++;
	while (*s->prompt && *s->prompt != DOUBLE_QUOTES)
	{
		(*size)++;
		s->prompt++;
	}
	(*size)++;
	s->prompt++;
}
