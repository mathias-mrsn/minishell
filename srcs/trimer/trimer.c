#include "minishell.h"

static void
	replace_dollars(t_mini *s, t_lexer *lexer, uint64_t *idx)
{
	uint64_t	end;
	char 		*begin;
	char 		*var;
	char 		*var_value;
	char 		*final;

	(void)s;
	begin = __strldup(lexer->argument, (*idx));
	end = (*idx) + 1;
	if (lexer->argument[(*idx) + 1] == DOLLAR)
	{
		end += 1;
		var_value = __get_exit_code__(s);
	}
	else
	{
		while(__isalnum(lexer->argument[end]) || lexer->argument[end] == '_')
			end++;
		var = __strldup(lexer->argument + (*idx) + 1, end - (*idx) - 1);
		var_value = __get_env_var__(s, var);
	}
	final = __strjoin(begin, __strjoin(var_value, __strdup(lexer->argument + end)));
	lexer->argument = final;
	(*idx) += __strlen(var_value);
}

static void
	delete_quotes(t_mini *s, t_lexer *lexer, uint64_t *idx, t_quotes quote)
{
	uint64_t	end;
	char 		*begin;
	char		*final;

	end = (*idx) + 1;
	while(lexer->argument[end] && lexer->argument[end] != (char)quote)
	{
		if (lexer->argument[end] == DOLLAR && quote == DOUBLE_QUOTES)
			replace_dollars(s, lexer, &end);
		else
			end++;
	}
	begin = __strjoin(__strldup(lexer->argument, (*idx)), __strldup(lexer->argument + (*idx) + 1, end - (*idx) - 1));
	final = __strjoin(begin, __strdup(lexer->argument + end + 1));
	lexer->argument = final;
	(*idx) = end - 1;
}

static void
	trimer_hub(t_mini *s, t_lexer *lexer)
{
	uint64_t	idx;

	idx = 0;
	while(lexer->argument[idx])
	{
		if (lexer->argument[idx] == SINGLE_QUOTES)
			delete_quotes(s, lexer, &idx, SINGLE_QUOTES);
		else if (lexer->argument[idx] == DOUBLE_QUOTES)
			delete_quotes(s, lexer, &idx, DOUBLE_QUOTES);
		else if (lexer->argument[idx] == DOLLAR)
			replace_dollars(s, lexer, &idx);
		else
			idx++;
	}
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
			trimer_hub(s, lexer);
		}
		lexer = lexer->next;
	}
	return (__SUCCESS);
}
