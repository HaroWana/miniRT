#include "miniRT.h"

static size_t	count_words(char const *s)
{
	size_t	words;
	size_t	new_word;

	words = 0;
	new_word = 0;
	while (*s)
	{
		if ((*s != ' ' || *s != '\t') && !new_word)
		{
			new_word = 1;
			words++;
		}
		else if (*s == ' ' || *s == '\t')
			new_word = 0;
		s++;
	}
	return (words);
}

static char	**calloc_cpy_word(char const *s, char **split,
			size_t s_len)
{
	size_t	i;
	size_t	i_split;
	size_t	word_len;

	i = 0;
	i_split = 0;
	word_len = 0;
	while (i < s_len + 1 && s_len > 0)
	{
		if (s[i] == ' ' || s[i] == '\t' || !s[i])
		{
			if (word_len > 0)
			{
				split[i_split] = (char *)calloc(word_len + 1, sizeof(char));
				if (split[i_split])
					strlcpy(split[i_split], &s[i - word_len], word_len + 1);
				word_len = 0;
				i_split++;
			}
		}
		else
			word_len++;
		i++;
	}
	return (split);
}

char	**split_words(char const *s)
{
	size_t	words;
	size_t	s_len;
	char	**split;

	if (!s)
		return (NULL);
	s_len = strlen(s);
	words = count_words(s);
	split = (char **)calloc(sizeof(char *), words + 1);
	if (!split)
		return (NULL);
	split = calloc_cpy_word(s, split, s_len);
	split[words] = NULL;
	return (split);
}
