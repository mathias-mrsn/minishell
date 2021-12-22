#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

int main()
{
    printf( "%s\n", readline( "minishell> " ) );
    return 0;
}