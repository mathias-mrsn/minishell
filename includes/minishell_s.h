#ifndef MINISHELL_S_H
# define MINISHELL_S_H

typedef struct s_cmd
{
	char *prompt;
	char **cmd;
}				t_cmd;

typedef struct s_env
{
	char **values;
}				t_env;

typedef struct s_mini
{
	t_env	*env;
	t_cmd	*cmd;
	uint64_t nbr_cmd;
}				t_mini;

#endif