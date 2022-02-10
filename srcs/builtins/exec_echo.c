#include "minishell.h"

 static t_boolean
 	__check_flag__(t_command *cmd, uint32_t *flags, uint64_t *idx)
 {
 	size_t	i;

 	while (cmd->args[(*idx)] && cmd->args[(*idx)][0] == '-')
 	{
 		i = 0;
 		while (cmd->args[(*idx)][++i] && cmd->args[(*idx)][i] == 'n')
 			(*flags) = 1;
 		if (i == 1 || cmd->args[(*idx)][i] != 0)
 		{
 			(*flags) = 0;
 			return (__FAILURE);
 		}
 		(*idx)++;
 	}
 	return (__SUCCESS);
 }

void
 	exec_echo(t_command *cmd)
 {
 	uint32_t	flags;
 	uint64_t	idx;

 	idx = 1;
 	flags = 0;
 	// (void)s;
 	__check_flag__(cmd, &flags, &idx);
 	while (cmd->args[idx])
 	{
 		__putstr(cmd->args[idx], 1);
 		if (cmd->args[idx + 1] != NULL)
 			__putstr(" ", 1);
 		idx++;
 	}
 	if (0 == flags)
 		__putstr("\n", 1);
}