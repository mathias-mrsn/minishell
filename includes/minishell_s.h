#ifndef MINISHELL_S_H
# define MINISHELL_S_H

typedef struct	s_redir
{
	char	*out;
	char	*in;
	int		type;
}				t_redir;

typedef struct s_pip
{
	char	*command;
	char	*option;
	char	**args;
	uint64_t	pip_index;
	t_redir	redir;
}				t_pip;

typedef struct s_cmd
{
	t_pip	*pip;
	uint64_t	pips_nbr;
}				t_cmd;

typedef struct s_mini
{
	t_cmd	*cmd; //Commandes separes par ';'
	char	**env;
	char	*path
	uint64_t shell_level;
	uint64_t	cmd_index;

}				t_mini;

#endif
