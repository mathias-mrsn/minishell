#include "minishell.h"

void    unvalid(char *arg)
{
    write(2, "unset: ", 7);
    write(2, arg, __strlen(arg));
    write(2, ": not a valid identifier\n", 25);
}

void    exec_unset(t_command *cmd)
{
    t_env   *env;
    t_env   *previous;
    int     i;
    int     ret;

    i = 1;

    while (cmd->args[i])
    {
        ret = 1;
        env = *(s()->env_lst);
        previous = NULL;
        while (env)
        {
            if (!__strncmp(cmd->args[i], env->key, (__strlen(cmd->args[i]) +1)))
            {
                free(env->full);
                free(env->key);
                free(env->value);
                if (previous)
                    previous->next = env->next;
                else
                    s()->env_lst = &(env->next);
                free(env);
                ret = 0;
                break ;
            }
            previous = env;
            env = env->next;
        }
        if (ret)
            unvalid(cmd->args[i]);
    i++;
    }
}