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

#endif