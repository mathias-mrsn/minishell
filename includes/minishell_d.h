#ifndef MINISHELL_D_H
# define MINISHELL_D_H

# define COMMAND 1
# define OPTIONS 2
# define ARGUMENT 3
# define OUTPUT 4
# define INPUT 5
# define PIPE 6

# define PROGRAM_NAME "minishell"
# define OPTION_CHARSET "-"
# define TOKEN_CS "|>< "
# define NBR_BUILDINS 7

/*
**	DICT	
*/

# define DICT_SIZE 23
# define DICT_LEFT 0
# define DICT_MIDDLE 1
# define DICT_RIGHT 2

/*
**	MALLOC
*/

# define LEXER_STOCKAGE	3
# define COMMAND_STOCKAGE 4
# define TRASH_STOCKAGE 127

#endif