#include "minishell.h"

uint8_t
	delete_quotes(t_mini *s)
{
	char *new_line;
	uint64_t	i1;
	uint64_t	i2;

	i1 = 0;
	i2 = 0;
	new_line = (char *)malloc(sizeof(char) * __strlen_except(s->whole_cmd, "\"\'") + 1);
	if (NULL == new_line)
		return (__FAILURE);
	while(s->whole_cmd[i1])
	{
		if (__SUCCESS == __is_charset(s->whole_cmd[i1], "\"\'"))
			i1 += 1;
		else
		{
			new_line[i2] = s->whole_cmd[i1];
			i1 += 1;
			i2 += 1;
		}
	}
	new_line[i2] = '\0';
	s->whole_cmd = new_line;
	return (__SUCCESS);
}