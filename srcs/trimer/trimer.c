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






















// void
// 	replace_dollars(t_mini *s, t_lexer *lexer, uint64_t *idx)
// {

// }

void
	delete_quotes(t_lexer *lexer, uint64_t *idx, t_quotes quote)
{
	uint64_t	end;
	char 		*begin;
	char		*final;

	end = (*idx) + 1;
	while(lexer->argument[end] && lexer->argument[end] != (char)quote)
	{
		// if (lexer->argument[end] == DOLLAR && quote == DOUBLE_QUOTES)
		// 	replace_dollars();
		// else
			end++;
	}
	begin = __strjoin(__strldup(lexer->argument, (*idx)), __strldup(lexer->argument + (*idx) + 1, end - (*idx) - 1));
	final = __strjoin(begin, __strdup(lexer->argument + end + 1));
	lexer->argument = final;
	(*idx) = end - 1;
}

void
	single_quotes_dollars(t_mini *s, t_lexer *lexer)
{
	uint64_t	idx;

	(void)s;
	idx = 0;
	while(lexer->argument[idx])
	{
		if (lexer->argument[idx] == SINGLE_QUOTES)
		{
			// printf("idx before = %llu\n", idx);
			delete_quotes(lexer, &idx, SINGLE_QUOTES);
			// printf(" -> %c ==> %s\n", str[idx], lexer->argument);
		}
		// if (lexer->argument == DOLLAR)
		// {

		// }
		else
			idx++;
	}
}

void
	double_quotes_dollars(t_mini *s, t_lexer *lexer)
{
	uint64_t	idx;

	(void)s;
	idx = 0;
	while(lexer->argument[idx])
	{
		if (lexer->argument[idx] == DOUBLE_QUOTES)
		{
			// printf("idx before = %llu\n", idx);
			delete_quotes(lexer, &idx, DOUBLE_QUOTES);
			// printf(" -> %c ==> %s\n", str[idx], lexer->argument);
		}
		// if (lexer->argument == DOLLAR)
		// {

		// }
		else
			idx++;
	}
}

void
	replace_dollars(t_mini *s, t_lexer *lexer)
{
	if (lexer->quotes == SINGLE_QUOTES)
		single_quotes_dollars(s, lexer);
	else if (lexer->quotes == DOUBLE_QUOTES)
		double_quotes_dollars(s, lexer);
	// else if (lexer->quotes == BOTH_QUOTES)
	// 	both_quotes_dollars(s, lexer);
	// else if (lexer->quotes == UNSET)
	// 	unset_quotes_dollars(s, lexer);
}


t_boolean
	trimer(t_mini *s)
{
	t_lexer *lexer;

	lexer = s->lexer;
	while (NULL != lexer)
	{
		if (lexer->token == ARGS)
		{
			replace_dollars(s, lexer);
		}
		lexer = lexer->next;
	}
	return (__SUCCESS);
}
