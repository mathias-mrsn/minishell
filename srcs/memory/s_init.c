#include "minishell.h"

t_mini
	*s(void)
{
	static t_mini *s;

	if (!s)
	{
		s = __malloc(sizeof(t_mini) * 1);
		if (!s)
			return (NULL);
	}
	return (s);
}