#include "minishell.h"

void    replace_pwd(char *old)
{
    char *buf;

    buf = NULL;
    buf = getcwd(buf, 999999);
    if (value_from_key("OLDPWD"))
        replace_env(__strjoin("OLDPWD=", old));
    else
         new_env(__strjoin("OLDPWD=", old));
    if (value_from_key("PWD"))
        replace_env(__strjoin("PWD=", buf));
    free(buf);
}

void    exec_cd(t_command *cmd)
{
    char *home;
    char *buf;

    buf = NULL;
    buf = getcwd(buf, 999999);
    home = NULL;
    if (cmd->args[2])
    {
        __puterr("cd: too many arguments\n");
        free(buf);
        return ;
    }
    if (!(cmd->args[1]))
    {
        home = value_from_key("HOME");
        if (home)
        {
            chdir(home);
            replace_pwd(buf);
        }
        else
            __putstr("minishell: cd: HOME not set\n", 2);
        free(buf);
        return ;
    }
    if (chdir(cmd->args[1]))
    {
        printf("cd: ");
        printf("%s", cmd->args[1]);
        printf(": No such file or directory\n");
        free(buf);
        return ;
    }
    else
    {
        replace_pwd(buf);
        free(buf);
    }
}
