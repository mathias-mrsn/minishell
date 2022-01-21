#ifndef MINISHELL_F_H
# define MINISHELL_F_H

/*
**	TRIM_QUOTES
*/

uint8_t			trim_quotes(t_mini *s);
char			*__catch_variable_name__(char *str);
uint64_t		__variable_name_length__(char *str);
uint8_t			__quotes_are_right__(t_mini *s);
uint8_t			get_env(t_mini *s, char **env);
char			*__get_env_value__(t_mini *s, char *tofind);
uint8_t			delete_quotes(t_mini *s);

/*
**	MEMORY
*/

t_mini		*s(void);

/*
**	PROMPT
*/

void			print_prompt(t_mini *s);

/*
**	LEXER
*/

void			lexer(t_mini *s);

/*
**	LIST TOOLS
*/

t_boolean		add_token_back(t_lexer **head, t_quotes quotes, t_token token);
t_boolean		add_token_front(t_lexer **head, t_quotes quotes, t_token token);
t_lexer			*find_last_elem(t_lexer **head);

/*
**	ERRORS
*/

void			__malloc_error__(char *type);

#endif