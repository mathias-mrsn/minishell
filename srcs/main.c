#include "minishell.h"

int main()
{
	char *buffer = NULL;

	char *res = getcwd(buffer, 500);
    printf( "%s\n",  res);
	printf( "%s\n", buffer);
    return 0;
}
