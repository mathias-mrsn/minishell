#include "minishell.h"

void    exec_pwd(t_command *cmd)
{
    char *buf;

	(void)cmd;
    buf = NULL;
    buf = getcwd(buf, 999999);
    __putstr(buf, 1);
    __putchar('\n', 1);
    free(buf);
}