#ifndef MINISHELL_S_H
# define MINISHELL_S_H

typedef struct s_detail
{
	char *string;
	int		type;
	int		id;
}				t_detail;

typedef struct s_cmd
{
	char *prompt;
	char **cmd;
	uint64_t	nbr_cmd;
	t_detail **cmd_splited;
}				t_cmd;

typedef struct s_env
{
	char **values;
}				t_env;

typedef struct s_mini
{
	t_env	*env;
	t_cmd	*parse;
}				t_mini;

#endif