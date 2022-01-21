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

// void
// 	__add_token_arg__(t_mini *s)
// {
// 	uint64_t	size;

// 	add_token_back(&s->lexer, UNSET, ARGS);
// 	while (__FAILURE == __is_charset(*s->prompt, TOKEN_CS))
// 	{
// 		if (*s->prompt == '\'')
// 			__fill_t_quote__(s, &size);
// 		else if (*s->prompt == '\"')
// 			__fill_t_quotes__(s, &size);
// 		else
// 			size++;
// 	}
	// find_last_elem(&s->lexer)->argument = copier jusqu'a size 

// }

t_boolean
	tokenizer(t_mini *s)
{
	if (*s->prompt == PIP)
		__add_token_pip__(s);
	else if (*s->prompt == R_RIGHT)
		__add_token_r_right__(s);
	else if (*s->prompt == R_LEFT)
		__add_token_r_left__(s);
	// else
	// 	__add_token_arg__(s);
	s->prompt++;
	return (__SUCCESS);
}

void
	show_tokens(t_mini *t)
{
	t_lexer *s;

	s = t->lexer;
	while (s)
	{
		printf("%c\n", s->token);
		s = s->next;
	}
}

void
	lexer(t_mini *s)
{
	const char *save = s->prompt;
	t_boolean error;

	error = __SUCCESS;
	if (NULL == s->prompt)
		return ;
	while ('\0' != *s->prompt)
	{
		if (error == __FAILURE)
			return ; //voir cette sortie
		if (__TRUE == __isempty(*s->prompt))
			skip_white_space(s);
		else
			error = tokenizer(s);
	}
	show_tokens(s);
	s->prompt = (char *)save;
}
