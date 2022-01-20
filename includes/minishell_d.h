#ifndef MINISHELL_D_H
# define MINISHELL_D_H

# define COMMAND 1
# define OPTIONS 2
# define ARGUMENT 3
# define OUTPUT 4
# define INPUT 5
# define PIPE 6

# define EOEV "\"\'; $" // END OF ENVIRONMENT VARIABLE
# define ET_CHARSET	"|;" // EXTRA TOKEN CHARSET
# define PROGRAM_NAME "minishell"
# define CMD_CHARSET "abcdefghijklmnopqrstuvwxyz.ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define REDIR_CHARSET "<>"
# define OPTION_CHARSET "-"

typedef enum e_token
{
	PIP = '|',
	R_LEFT = '<',
	R_RIGHT = '>',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTES = '\"',
	DR_LEFT,
	DR_RIGHT,
	OPTION,
	ARGS,
	NONE
}			t_token;

typedef enum e_quotes
{
	SINGLE_QUOTES,
	DOUBLE_QUOTES,
	MIX_QUOTES,
	NONE
}			t_quotes;

#endif