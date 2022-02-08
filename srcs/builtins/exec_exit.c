#include "minishell.h"

void    free_env_lst(void)
{
    t_env   **env_lst;
    t_env   *current;
    t_env   *tmp;

    env_lst = s()->env_lst;
    current = *env_lst;
    while (current)
    {
        free(current->full);
        free(current->key);
        free(current->value);
        tmp = current;
        current = current->next;
        free(tmp);
    }
    free(env_lst);
}

void    exec_exit(t_command *cmd)
{
    if (!cmd->args[1])
    {
	    close_open_files();
        free_env_lst();
        //clear history;
        __putstr("exit\n", 1);
        exit(1);
    }
}