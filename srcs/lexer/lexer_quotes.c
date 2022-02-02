/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:17:29 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/02 16:13:57 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_boolean
	__set_quote__(t_mini *s, char **str, t_lexer *lexer)
{
	if (lexer->quotes == SINGLE_QUOTES || lexer->quotes == DOUBLE_QUOTES)
		lexer->quotes = MIX_QUOTES;
	else
		lexer->quotes = SINGLE_QUOTES;
	(*str)++;
	while (**str != '\'' && **str != '\0')
		(*str)++;
	if (!(**str))
		return (__unclosed_quote__(s, 0), __TRUE);
	(*str)++;
	return (__FALSE);
}

static t_boolean
	__set_quotes__(t_mini *s, char **str, t_lexer *lexer)
{
	if (lexer->quotes == SINGLE_QUOTES || lexer->quotes == SINGLE_QUOTES)
		lexer->quotes = MIX_QUOTES;
	else
		lexer->quotes = DOUBLE_QUOTES;
	(*str)++;
	while (**str != '\"' && **str != '\0')
		(*str)++;
	if (!(**str))
		return (__unclosed_quote__(s, 1), __TRUE);
	(*str)++;
	return (__FALSE);
}

static void
	change_t_quotes(t_mini *s, t_lexer *lexer)
{
	char *str;

	str = lexer->argument;
	while (*str)
	{
		if (*str == '\'')
			__set_quote__(s, &str, lexer);
		else if (*str == '\"')
			__set_quotes__(s, &str, lexer);
		else
			str++;
	}
}

void
	set_t_quotes(t_mini *s)
{
	t_lexer	*tmp;

	tmp = s->lexer;
	while (NULL != tmp)
	{
		if (tmp->token == ARGS)
			change_t_quotes(s, tmp);
		tmp = tmp->next;
	}
}
