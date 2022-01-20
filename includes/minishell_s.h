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

typedef struct s_lexer
{
	t_quotes		quotes;
	t_token			type;	
	struct s_lexer 	*previous;
	struct s_lexer 	*next;
}				t_lexer;

typedef struct s_mini
{
	t_lexer	*lexer; //Commandes separes par ';'
	char	**env;
	char	*path;
	char	*prompt;
	uint8_t	exit_status;
	uint64_t shell_level;
	uint64_t	nbr_cmd;

}				t_mini;

#endif
