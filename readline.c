# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <libc.h>

int main()
{
	char *buffer = NULL;

	char *res = getcwd(buffer, 500);
    printf( "%s\n",  res);
	printf( "%s\n", buffer);
    return 0;
}
