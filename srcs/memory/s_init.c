#include "minishell.h"

t_mini
	*s(void)
{
	static t_mini *s;

	if (!s)
	{
		s = malloc(sizeof(t_mini) * 1);
		__memset(s, 0, sizeof(t_mini));
		if (!s)
			return (NULL);
	}
	return (s);
}