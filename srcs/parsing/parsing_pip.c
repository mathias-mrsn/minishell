#include "minishell.h"

uint8_t
	get_cmd(t_pip *pip, char **str)
{
	size_t	len;
	char 	*tmp;

	tmp = (*str);
	len = 0;
	while (*tmp && (*tmp < 9 || *tmp > 13) && *tmp != ' ')
	{
		tmp++;
		len++;
	}
	printf("{%zu}\n", len);
	pip->command = (char *)malloc(sizeof(char) * (len + 1));
	if (NULL == pip->command)
		return (__FAILURE);
	__strlcpy(pip->command, (const char *)(*str), len + 1);
	(*str) = tmp;
	return (__SUCCESS);
}

uint8_t
	get_option(t_pip *pip, char **str)
{
	size_t	len;
	char 	*tmp;
	// char 	*mall;

	tmp = (*str);
	len = 0;
	while (*tmp && (*tmp < 9 || *tmp > 13) && *tmp != ' ')
	{
		tmp++;
		len++;
	}
	printf("{%zu}\n", len);
	if (NULL == pip->option)
	{
		pip->option = (char *)malloc(sizeof(char) * (len + 1));
		if (NULL == pip->option)
			return (__FAILURE);
		__strlcpy(pip->option, (const char *)(*str) + 1, len);
	}
	// else
	// {
	// 	mall = (char *)malloc(sizeof(char) * (len + __strlen(pip->option) + 1));
	// 	if (NULL == mall)
	// 		return (__FAILURE);
	// 	__strlcat(mall, (const char *)(*str), len + 1);
	// 	free(pip->option);
	// 	pip->option = (char *)mall;
	// }
	(*str) = tmp;
	return (__SUCCESS);
}

uint8_t
	parse_pip(t_mini *s, t_pip *pip)
{
	char *str;

	str = pip->full;
	(void)s;
	while (*str)
	{
		if (__SUCCESS == __is_charset(*str, CMD_CHARSET) && NULL == pip->command)
			get_cmd(pip, &str);
		else if (__SUCCESS == __is_charset(*str, OPTION_CHARSET) && __FAILURE == __is_charset(str[1], OPTION_CHARSET))
			get_option(pip, &str);
		// else if (__SUCCESS == __is_charset(*str, REDIR_CHARSET))
		// 	redir();
		// else
		// 	get_argument(pip, &str);
		str++;
	}
	return (__SUCCESS);
}

uint8_t
	parse_hub(t_mini *s)
{
	uint64_t	i;
	uint64_t	j;

	i = 0;
	while (i < s->nbr_cmd)
	{
		j = 0;
		while (j < s->cmd[i].nbr_pip)
		{
			printf("here");
			if (__FAILURE == parse_pip(s, &s->cmd[i].pip[j]))
				return (__FAILURE);
			j++;
		}
		i++;
	}
	return (__SUCCESS);
}