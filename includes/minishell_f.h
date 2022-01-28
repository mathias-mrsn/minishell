#ifndef MINISHELL_F_H
# define MINISHELL_F_H

/*
**	ENV
*/

uint8_t			get_env(t_mini *s, char **env);

/*
**	TRIM_QUOTES
*/

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

t_boolean			lexer(t_mini *s);
void				set_t_quotes(t_mini *s);
t_boolean			lexer_checker(t_mini *s);
void				__skip_white_space__(t_mini *s);
void				__add_token_pip__(t_mini *s);
void				__add_token_r_right__(t_mini *s);
void				__add_token_r_left__(t_mini *s);
void				__add_token_arg__(t_mini *s);



/*
**	TRIMER
*/

t_boolean			trimer(t_mini *s);

/*
**	PARSER
*/

t_boolean			parsing(t_mini *s);

/*
**	LIST TOOLS
*/

t_boolean			add_token_back(t_lexer **head, t_quotes quotes, t_token token);
t_boolean			add_token_front(t_lexer **head, t_quotes quotes, t_token token);
t_lexer				*find_last_elem(t_lexer **head);
t_command			*add_command_front(t_command **head);
t_command			*add_command_back(t_command **head);

/*
**	ERRORS
*/

void			__malloc_error__(char *type);

#endif