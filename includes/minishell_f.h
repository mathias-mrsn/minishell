#ifndef MINISHELL_F_H
# define MINISHELL_F_H

/*
**	ENV
*/

uint8_t			get_env(t_mini *s, char **env);
char            *value_from_key(char *key);
int             in_env_from_key(char *key);
void            new_env(char *new);
void            replace_env(char *new);
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
void				set_quotes(t_mini *s);
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
t_boolean			set_here_doc(t_mini *s, t_command *cmd, t_lexer **lexer);
void				cmd_parsing(t_command *cmd, t_lexer **lexer);
void				output_parsing(t_mini *s, t_command *cmd, t_lexer **lexer);

/*
**	WILDCARD
*/

void				wildcard(t_mini *s, t_command *cmd, char *str);
t_boolean			__file_match_with_wc__(char *file, const char **wc, int start, int end);
void				__swap__(char **a, char **b);
void				__sort_args__(char ***list);
void				__add_to_cmd__(t_command *cmd, char **strs, char *add_front);





/*
**	LIST TOOLS
*/

t_boolean			add_token_back(t_lexer **head, t_quotes quotes, t_token token);
t_boolean			add_token_front(t_lexer **head, t_quotes quotes, t_token token);
t_lexer				*find_last_elem(t_lexer **head);
t_command			*add_command_front(t_command **head);
t_command			*add_command_back(t_command **head);
void				input_parsing(t_mini *s, t_command *cmd, t_lexer **lexer);

/*
**	ERRORS
*/

void			__malloc_error__(char *type);
void			__token_syntax_error__(t_mini *s, int error_value);
void			__unclosed_quote__(t_mini *s, int error_value);
void			__file_dont_exist__(t_mini *s, char *str);
void			__error_wildcard__(t_mini *s);

/*
**	EXEC
*/

t_boolean		exec_builtins(t_command *cmd);

/*
**	BUILTINS
*/

void                exec_cd(t_command *cmd);
void                exec_echo(t_command *cmd);
void                exec_env(t_command *cmd);
void                exec_exit(t_command *cmd);
void                exec_export(t_command *cmd);
void                exec_pwd(t_command *cmd);
void                exec_unset(t_command *cmd);

/*
** EXEC
*/

void	            exec_cmds(void);
void	            close_open_files(void);
void	            close_prev_pipe(t_command *cmd);
int 	            check_pipe(t_command *cmd);
void	            exec(t_command *cmd);
void	            switch_io(t_command *cmd);
int	                is_builtin(t_command *cmd);
void	            create_heredoc(t_command *cmd);

void	            add_env_back(t_env **alst, t_env *new);
t_boolean			exec_builtins(t_command *cmd);


#endif