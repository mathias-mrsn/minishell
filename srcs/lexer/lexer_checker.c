/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:20:15 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/12 11:51:34 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	*__create_dictionary__(void)
{
	static const t_dict	dict[DICT_SIZE] = {{{R_RIGHT, PIP, NUL}, 0},
	{{DR_RIGHT, PIP, PIP}, 0}, {{R_LEFT, PIP, NONE}, 0},
	{{NONE, R_LEFT, NUL}, 5}, {{NONE, R_LEFT, R_RIGHT}, 2},
	{{NONE, R_LEFT, DR_RIGHT}, 4}, {{NONE, R_LEFT, R_LEFT}, 1},
	{{NONE, R_LEFT, DR_LEFT}, 3}, {{NONE, DR_LEFT, NUL}, 5},
	{{NONE, DR_LEFT, R_RIGHT}, 2}, {{NONE, DR_LEFT, DR_RIGHT}, 4},
	{{NONE, DR_LEFT, R_LEFT}, 1}, {{NONE, DR_LEFT, DR_LEFT}, 3},
	{{NONE, R_RIGHT, NUL}, 5}, {{NONE, R_RIGHT, R_RIGHT}, 2},
	{{NONE, R_RIGHT, DR_RIGHT}, 4}, {{NONE, R_RIGHT, R_LEFT}, 1},
	{{NONE, R_RIGHT, DR_LEFT}, 3}, {{NONE, DR_RIGHT, NUL}, 5},
	{{NONE, DR_RIGHT, R_RIGHT}, 2}, {{NONE, DR_RIGHT, DR_RIGHT}, 4},
	{{NONE, DR_RIGHT, R_LEFT}, 1}, {{NONE, DR_RIGHT, DR_LEFT}, 3}};

	return ((void *)dict);
}

static t_boolean
	__check_left__(t_lexer *lexer, t_dict dict)
{
	if (dict.array[DICT_LEFT] == NUL && lexer->prev == NULL)
		return (__FAILURE);
	else if (lexer->prev != NULL)
	{
		if (dict.array[DICT_LEFT] == lexer->prev->token)
			return (__FAILURE);
	}
	return (__SUCCESS);
}

static t_boolean
	__check_right__(t_lexer *lexer, t_dict dict)
{
	if (dict.array[DICT_RIGHT] == NUL && lexer->next == NULL)
		return (__FAILURE);
	else if (lexer->next != NULL)
	{
		if (dict.array[DICT_RIGHT] == lexer->next->token)
			return (__FAILURE);
	}
	return (__SUCCESS);
}

static t_boolean
	check_in_dict(t_mini *s, t_lexer *lexer, const t_dict *dict)
{
	uint64_t	idx;

	idx = 0;
	while (idx < DICT_SIZE)
	{
		if (dict[idx].array[DICT_MIDDLE] == lexer->token)
		{
			if (dict[idx].array[DICT_LEFT] != NONE
				&& __FAILURE == __check_left__(lexer, dict[idx]))
				return (__token_syntax_error__(s, dict[idx].error), __FAILURE);
			if (dict[idx].array[DICT_RIGHT] != NONE
				&& __FAILURE == __check_right__(lexer, dict[idx]))
				return (__token_syntax_error__(s, dict[idx].error), __FAILURE);
		}
		idx++;
	}
	return (__SUCCESS);
}

t_boolean
	lexer_checker(t_mini *s)
{
	const t_dict	*dict = (const t_dict *)__create_dictionary__();
	t_lexer			*lexer;

	lexer = s->lexer;
	while (lexer && s->error != __TRUE)
	{
		if (__FAILURE == check_in_dict(s, lexer, dict))
			return (__FAILURE);
		lexer = lexer->next;
	}
	return (__SUCCESS);
}
