/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:20:27 by mamaurai          #+#    #+#             */
/*   Updated: 2022/01/28 12:43:03 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean
	tokenizer(t_mini *s)
{
	if (*s->prompt == PIP)
		__add_token_pip__(s);
	else if (*s->prompt == R_RIGHT)
		__add_token_r_right__(s);
	else if (*s->prompt == R_LEFT)
		__add_token_r_left__(s);
	else
		__add_token_arg__(s);
	return (__SUCCESS);
}

t_boolean
	lexer(t_mini *s)
{
	const char *save = s->prompt;
	t_boolean error;

	error = __SUCCESS;
	if (NULL == s->prompt)
		return (__SUCCESS);
	while ('\0' != *s->prompt)
	{
		if (error == __FAILURE)
			return (__FAILURE); //voir cette sortie
		if (__TRUE == __isempty(*s->prompt))
			__skip_white_space__(s);
		else
			error = tokenizer(s);
	}
	set_t_quotes(s);
	if (__FAILURE == lexer_checker(s))
		return (__FAILURE);
	s->prompt = (char *)save;
	return (__SUCCESS);
}
