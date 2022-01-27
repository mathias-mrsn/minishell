#ifndef MINISHELL_S_H
# define MINISHELL_S_H

// typedef struct	s_redir
// {
// 	char	*out;
// 	char	*in;
// 	int		type;
// }				t_redir;

// typedef struct s_pip
// {
// 	char	*full;
// 	char	*command;
// 	char	*option;
// 	char	**args;
// 	t_redir	redir;
// }				t_pip;

typedef enum e_token
{
	PIP = '|',
	R_LEFT = '<',
	R_RIGHT = '>',
	DR_LEFT,
	DR_RIGHT,
	ARGS,
	NONE
}			t_token;

typedef enum e_quotes
{
	SINGLE_QUOTES,
	DOUBLE_QUOTES,
	MIX_QUOTES,
	UNSET,
	ERROR
}			t_quotes;

typedef struct s_lexer
{
	t_quotes		quotes;
	t_token			token;
	char			*argument;
	t_boolean		readed;
	struct s_lexer 	*prev;
	struct s_lexer 	*next;
}				t_lexer;

typedef struct s_command
{
	char 			*command;
	char			**args;
	t_token			type;
	int				tube[2];
	int 			infile;
	int				outfile;
	char			*limiter;
	int				nbr_cmd;
	pid_t			child;
	t_boolean		builtin;
	struct s_command	*next;
	struct s_command	*prev;
}				t_command;

typedef struct s_mini
{
	t_lexer			*lexer; //Commandes separes par ';'
	t_command		*cmd;
	char			**env;
	char			*path;
	char			*prompt;
	uint8_t			exit_status;
	uint64_t 		shell_level;
}				t_mini;

#endif

/*********************** ERRORS CASES
 * > ""
 * > <
 * < >
 * >> >
 * > >>
 * > >
 * > empty
 * 
 */
