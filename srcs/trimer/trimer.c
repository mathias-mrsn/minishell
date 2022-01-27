#include "minishell.h"

t_boolean
	dollar_trimer(t_mini *s, char **str, uint64_t *i)
{
	(void)s;
	(void)str;
	(void)i;
	return (__SUCCESS);
}

t_boolean
	checker_args(t_mini *s, t_lexer *lexer)
{
	char *str;
	uint64_t	idx;

	idx = 0;
	if (NULL == lexer->argument)
		return (__SUCCESS);
	str = lexer->argument;
	while (str[idx])
	{
		if ('$' == str[idx])
			dollar_trimer(s, &str, &idx);
		idx++;
	}
	return (__TRUE);
}

t_boolean
	trimer(t_mini *s)
{
	t_lexer *lexer;

	lexer = s->lexer;
	while (NULL != lexer)
	{
		if (lexer->token == ARGS)
			checker_args(s, lexer);
		lexer = lexer->next;
	}
	return (__SUCCESS);
}