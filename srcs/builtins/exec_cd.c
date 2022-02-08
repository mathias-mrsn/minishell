#include "minishell.h"

void    exec_cd(t_command *cmd)
{
    char *home;

    home = NULL;
    if (cmd->args[2])
    {
        __puterr("cd: too many arguments\n");
        return ;
    }
    if (!(cmd->args[1]))
    {
        home = getenv("HOME");
        if (home)
            chdir(home);
        return ;
    }
    if (chdir(cmd->args[1]))
    {
        printf("cd: ");
        printf("%s", cmd->args[1]);
        printf(": No such file or directory\n");
        return ;
    }
}
