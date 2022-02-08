#include "minishell.h"

void    exec_pwd(void)
{
    char *buf;

    buf = NULL;
    buf = getcwd(buf, 999999);
    __putstr(buf, 1);
    __putchar('\n', 1);
    free(buf);
}