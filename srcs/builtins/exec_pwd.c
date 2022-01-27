#include "minishell.h"

void    exec_pwd(t_command *cmd)
{
    char *buf;

	(void)cmd;
    buf = NULL;
    buf = getcwd(buf, 999999);
    write(1, buf, __strlen(buf));
    write(1, "\n", 1);
    free(buf);
}