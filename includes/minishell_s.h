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
	char	*full;
	char	*command;
	char	*option;
	char	**args;
	t_redir	redir;
}				t_pip;

typedef struct s_cmd
{
	t_pip		*pip;
	char		*full_cmd;
	uint64_t	nbr_pip;
}				t_cmd;

typedef struct s_mini
{
	t_cmd	*cmd; //Commandes separes par ';'
	char	**env;
	char	*path;
	char	*prompt;
	char	*whole_cmd;
	uint8_t	exit_status;
	uint64_t shell_level;
	uint64_t	nbr_cmd;

}				t_mini;

#endif
