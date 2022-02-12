#include "minishell.h"

void    exec_env(void)
{
    t_env    *env;

    env = *(s()->env_lst);

    if (!env)
        return ;
    while (env)
    {
		if (env->in_env == 1)
		{
			__putstr(env->key, 1);
			__putstr("=", 1);
			__putstr(env->value, 1);
			__putchar('\n', 1);
		}
		env = env->next;
    }
} 
