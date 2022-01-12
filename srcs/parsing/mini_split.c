#include "minishell.h"

static uint8_t
	__is_in_squotes__(const char *str, uint64_t index)
{
	uint64_t			i;
	uint64_t	count;

	count = 0;
	i = 0;
	while(str[i] && i < index)
	{
		if (str[i] == '\'' || str[i] == '\"')
			count += 1;
		i += 1;
	}
	return ((count + 1) % 2);
}

static uint8_t
	mini_is_c_(char s, char c, uint64_t i, const char *str)
{
	if (s == c && __FAILURE == __is_in_squotes__(str, i))
		return (1);
	return (0);
}

static uint64_t
	mini_ft_count_word(const char *str, char c)
{
	uint64_t	i;
	uint64_t	len;

	len = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] && !mini_is_c_(str[i], c, i, str))
			++len;
		while (str[i] && !mini_is_c_(str[i], c, i, str))
			++i;
	}
	return (len);
}

static uint64_t
	mini_ft_word_len(const char *str, char c)
{
	uint64_t	len;
	uint64_t	i;

	len = 0;
	i = -1;
	while (str[++i] && !mini_is_c_(str[i], c, i, str))
		++len;
	return (len);
}

char
	**mini_split(char const *str, char c)
{
	char	**strs;
	uint64_t		len;
	uint64_t		i;
	uint64_t		j;

	if (!str)
		return (NULL);
	strs = (char **)__malloc(sizeof(char *) * (mini_ft_count_word(str, c) + 1));
	if (!strs)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && j < mini_ft_count_word(str, c))
	{
		while (str[i] && mini_is_c_(str[i], c, i, str))
			++i;
		len = mini_ft_word_len(str + i, c);
		strs[j] = (char *)__malloc(sizeof(char) * len + 1);
		if (!strs[j])
			return (NULL);
		__strlcpy(strs[j++], str + i, len + 1);
		i += len;
	}
	strs[j] = NULL;
	return (strs);
}
