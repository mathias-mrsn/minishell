#ifndef MINISHELL_F_H
# define MINISHELL_F_H

/*
		TRIM_QUOTES
*/

uint8_t		trim_quotes(t_mini *s);
char		*__catch_variable_name__(char *str);
uint64_t	__variable_name_length__(char *str);
uint8_t		__quotes_are_right__(t_mini *s);
uint8_t		get_env(t_mini *s, char **env);
char		*__get_env_value__(t_mini *s, char *tofind);
uint8_t		delete_quotes(t_mini *s);

/*
		SPLIT COMMANDS
*/	

uint8_t		split_shell(t_mini *s);
uint8_t		delete_quotes(t_mini *s);
char		**mini_split(char const *str, char c);
uint8_t		split_pips(t_mini *s);
uint8_t		__is_empty__(char *str);

/*
		PARSING
*/

uint8_t		parse_hub(t_mini *s);

/*
		MEMORY
*/

t_mini		*s(void);

#endif