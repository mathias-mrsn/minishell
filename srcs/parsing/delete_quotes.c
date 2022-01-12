#include "minishell.h"

static char
	*__str_wo_quotes__(char *str)
{
	char 		*new_str;
	uint64_t	index;
	uint64_t	index2;

	index = 0;
	index2 = 0;
	new_str = NULL;
	if (!str)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (__strlen_except(str, "\'\"") + 1));
	if (NULL == new_str)
		return (NULL);
	while (str[index])
	{
		if (__FAILURE == __is_charset(str[index], "\'\""))
			new_str[index2++] = str[index];
		index += 1;
	}	
	new_str[index2] = '\0';
	return (new_str);
}

uint8_t
	delete_quotes(t_mini *s)
{
	uint64_t	i1;
	uint64_t	i2;

	i1 = 0;
	i2 = 0;
	while(i1 < s->nbr_cmd)
	{
		i2 = 0;
		while (i2 < s->cmd[i1].nbr_pip)
		{
			s->cmd[i1].pip[i2].full = __str_wo_quotes__(s->cmd[i1].pip[i2].full);
			if (NULL == s->cmd[i1].pip[i2].full)
				return (__FAILURE);
			i2 += 1;
		}
		i1 += 1;
	}
	return (__SUCCESS);
}

// fonction pour supprimer des les quotes d'une chaine 
