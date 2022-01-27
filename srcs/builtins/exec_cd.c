#include "minishell.h"

void    exec_cd(t_command *cmd)
{
    if (cmd->args[2])
    {
        write(2, "cd: too many arguments\n", 23);
        return ;
    }
    if (!chdir(cmd->args[1]))
    {
        write(2, "cd: ", 4);
        write(2, cmd->args[1], __strlen(cmd->args[1]));
        write(2, ": No such file or directory\n", 28);
        return ;
    }
}
