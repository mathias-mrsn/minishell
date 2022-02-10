#include "minishell.h"

void		sort_env(char **tab, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (tab && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (__strncmp(tab[i], tab[i + 1], __strlen(tab[i]) + 1) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

char    *value_from_key(char *key)
{
    t_env   *current;

    current = *(s()->env_lst);
    while (current)
    {
        if (!__strncmp(current->key, key, (__strlen(key) + 1)))
            return (current->value);
        current = current->next;
    }
    return (NULL);
}

int    in_env_from_key(char *key)
{
    t_env   *current;

    current = *(s()->env_lst);
    while (current)
    {
        if (!__strncmp(current->key, key, (__strlen(key) + 1)))
            return (current->in_env);
        current = current->next;
    }
    return (0);
}

void    print_sorted_env(void)
{
    char    **env;
    t_env   *lst;
    int     size;

    size = 0;
    lst = *(s()->env_lst);
	while(lst)
    {
		size++;
        lst = lst->next;
    }
    env = malloc(sizeof(char *) * (size + 1));
    size = 0;
    lst = *(s()->env_lst);
    while(lst)
    {
        env[size] = __mstrdup(lst->key, __DONT_STOCK_MEM);
        size++;
        lst = lst->next;
    }
    env[size] = NULL;
    sort_env(env, size);
    size = 0;
    while (env[size])
    {
        __putstr("declare -x ", 1);
        __putstr(env[size] , 1);
        if (in_env_from_key(env[size]))
        {
            __putstr("=", 1);
            __putchar('"', 1);
            __putstr(value_from_key(env[size]), 1);
            __putchar('"', 1);
        }
        __putstr("\n", 1);
        //free(env[size]);
        size++;
    }
    //free(env);
}

int     new_env_type(char *new)
{
    char    **splited;
    t_env   *current;
    int     concat;

    concat = 0;
    if (!__isalpha(new[0]))
        return (0);
    splited = __msplit(new, '=', __DONT_STOCK_MEM);
    current  = *(s()->env_lst);
    if (splited[0][__strlen(splited[0]) - 1] == '+')
        concat = 1;
    while (current)
    {
        if (!__strncmp(splited[0], current->key, (__strlen(splited[0]) - concat)) && !current->key[__strlen(splited[0])])
        {
            free(splited[0]);
            if (splited[1])
                free(splited[1]);
            free(splited);
            if (concat)
                return (3);
            return(1);
        }
        else
            current = current->next;
    }
    free(splited[0]);
    if (splited[1])
        free(splited[1]);
    free(splited);
    return (2);
}

void    new_env(char *new)
{
    t_env    *new_elem;
    char    **splited;

    new_elem = malloc(sizeof(t_env));
    if (!new)
        return ;
    splited = __msplit(new, '=', __DONT_STOCK_MEM);
    new_elem->full = __mstrdup(new, __DONT_STOCK_MEM);
    new_elem->key = splited[0];
    if (splited[1])
        new_elem->value = splited[1];
    else
        new_elem->value = NULL;
    if (__strchr(new, '='))
        new_elem->in_env = 1;
    else
        new_elem->in_env = 0;
    new_elem->next= NULL;
    add_env_back(s()->env_lst, new_elem);
    free(splited);
}

void    replace_env(char *new)
{
    char    **splited;
    t_env   *current;

    splited = __msplit(new, '=', __DONT_STOCK_MEM);
    current = *(s()->env_lst);
    while (current)
    {
        if (!__strncmp(current->key, splited[0], (__strlen(splited[0]) + 1)))
        {
            free(current->value);
            if (splited[1])
                current->value = splited[1];
            else
                current->value = NULL;
            if (__strchr(new, '='))
                current->in_env = 1;
            free(splited[0]);
            free(splited);
            current->full = new;
            return ;
        }
        current = current->next;
    }
}

void    concat_env(char *new)
{
    char    **splited;
    t_env   *current;
    char    *tmp;

    splited = __msplit(new, '=', __DONT_STOCK_MEM);
    current = *(s()->env_lst);
    while (current)
    {
        if (!__strncmp(current->key, splited[0], (__strlen(current->key))) && splited[0][__strlen(current->key)] == '+')
        {
            if (splited[1])
            {
                tmp = __mstrjoin(current->value, splited[1], __DONT_STOCK_MEM);
                free(current->value);
                current->value = tmp;
            }
            splited[0][__strlen(splited[0]) - 1] = 0;
            tmp = __mstrjoin(splited[0], "=", __DONT_STOCK_MEM);
            free(current->full);
            if (current->value)
                current->full = __mstrjoin(tmp, current->value, __DONT_STOCK_MEM);
            else
                current->full = __mstrdup(tmp, __DONT_STOCK_MEM);
            current->in_env = 1;
            free(tmp);
            free(splited[0]);
            if (splited[1])
                free(splited[1]);
            return ;
        }
        current = current->next;
    }
}

void    invalid_env(char *new)
{
    write(2, "export: ", 8);
    write(2, new, __strlen(new));
    write(2, ": not a valid identifier\n", 25);
}

void    exec_export(t_command *cmd)
{
    int i;
    int type;

    if (!cmd->args[1])
        print_sorted_env();
    else
    {
        i = 1;
        while (cmd->args[i])
        {
            type = new_env_type(cmd->args[i]);
            if (!type)
                invalid_env(cmd->args[i]);
            else if (type == 1)
                replace_env(cmd->args[i]);
            else if (type == 2)
                new_env(cmd->args[i]);
            else if (type == 3)
                concat_env(cmd->args[i]);
            i++;
        }
    }
    return ;
}