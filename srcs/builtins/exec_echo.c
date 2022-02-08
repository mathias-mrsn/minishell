#include "minishell.h"

void    exec_echo(t_command *cmd)
{
    int option;
    int i;

    i = 1;
    if (cmd->args[1] && !__strncmp("-n", cmd->args[1], 3))
        option = 1;
    else
        option = 0;
    while (cmd->args[i + option])
    {
        __putstr(cmd->args[i + option], 1);
        i++;
    }
    if (!option)
        __putchar('\n', 1);
}