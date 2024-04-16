#include "miniRT.h"

static size_t	count_words(char const *s, t_data *d)
{
	size_t	words;
	size_t	new_word;

	words = 0;
	new_word = 0;
	while (*s)
	{
		if ((*s != d->c1 || *s != d->c2) && !new_word)
		{
			new_word = 1;
			words++;
		}
		else if (*s == d->c1 || *s == d->c2)
			new_word = 0;
		s++;
	}
	return (words);
}

static char	**calloc_cpy_word(char const *s, t_data *d, char **split,
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
		if (s[i] == d->c1 || s[i] == d->c2 || !s[i])
		{
			if (word_len > 0)
			{
				split[i_split] = (char *)ft_calloc(word_len + 1, sizeof(char));
				if (split[i_split])
					ft_strlcpy(split[i_split], &s[i - word_len], word_len + 1);
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

char	**ft_split2(char const *s, t_data *d)
{
	size_t	words;
	size_t	s_len;
	char	**split;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	words = count_words(s, d);
	split = (char **)ft_calloc(sizeof(char *), words + 1);
	if (!split)
		return (NULL);
	split = calloc_cpy_word(s, d, split, s_len);
	split[words] = NULL;
	return (split);
}
