#ifndef MINISHELL_D_H
# define MINISHELL_D_H

# define TOO_MANY_ARG_ERR "minishell: too many arguments to launch\n"

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

/*
**	PROG_STATES
*/

# define HEREDOC_CHILD 1
# define HEREDOC_FATHER 2

#endif