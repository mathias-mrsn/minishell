#include "minishell.h"

void
	skip_white_space(t_mini *s)
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

void
	show_tokens(t_mini *t)
{
	t_lexer *s;

	s = t->lexer;
	while (s)
	{
		if (s->token == ARGS)
			printf("%s\n", s->argument);
		else
			printf("%c\n", s->token);
		s = s->next;
	}
}


















t_boolean
	__set_quote__(char *str, t_lexer *lexer)
{
	if (lexer->quotes == SINGLE_QUOTES || lexer->quotes == DOUBLE_QUOTES)
		lexer->quotes = MIX_QUOTES;
	else
		lexer->quotes = SINGLE_QUOTES;
	while (*str != '\'' && *str != '\0')
		str++;
	if (!(*str))
		return (__TRUE);
	str++;
	return (__FALSE);
}

t_boolean
	__set_quotes__(char *str, t_lexer *lexer)
{
	if (lexer->quotes == SINGLE_QUOTES || lexer->quotes == SINGLE_QUOTES)
		lexer->quotes = MIX_QUOTES;
	else
		lexer->quotes = DOUBLE_QUOTES;
	while (*str != '\"' && *str != '\0')
		str++;
	if (!(*str))
		return (__TRUE);
	str++;
	return (__FALSE);
}

void
	change_t_quotes(t_lexer *lexer)
{
	char *str;

	str = lexer->argument;
	while (*str)
	{
		if (*str == '\'')
			__set_quote__(str, lexer);
		else if (*str == '\"')
			__set_quotes__(str, lexer);
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
			change_t_quotes(tmp);
		tmp = tmp->next;
	}
}








t_boolean
	lexer_checker(t_mini *s)
{
	t_lexer *tmp;

	tmp = s->lexer;
	while (tmp)
	{
		// if (!__redix_mixed__(tmp))
			return (__FAILURE);
	}
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
			skip_white_space(s);
		else
			error = tokenizer(s);
	}
	set_t_quotes(s);
	show_tokens(s);
	if (__FAILURE == lexer_checker(s))
		return (__FAILURE);
	s->prompt = (char *)save;
	return (__SUCCESS);
}
