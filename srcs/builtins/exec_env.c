#include "minishell.h"

void    exec_env(t_command *cmd)
{
    t_env    *env;

	(void)cmd;
    env = *(s()->env_lst);
    if (!env)
        return ;
    while (env)
    {
        if (env->in_env)
        {
            __putstr(env->full, 1);
            __putchar('\n', 1);
        }
        env = env->next;
    }
}