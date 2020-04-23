/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 20:11:56 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/04/22 17:43:31 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	count_words(char *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
			count++;
		i++;
	}
	return (count);
}

static int		make_words(char ***ret, char *s, char c)
{
	size_t	i;
	size_t	start;
	size_t	count;

	i = 0;
	start = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			(*ret)[count] = ft_strsub(s, start, i - start);
			if ((*ret)[count] == 0)
				return (0);
			count++;
		}
		if (s[i] != 0)
			i++;
	}
	return (1);
}

char			**ft_strsplit(const char *s, char c)
{
	char	**ret;
	size_t	words;
	int		i;

	if (!s)
		return (NULL);
	words = count_words((char*)s, c);
	if (words == 0)
		return (NULL);
	ret = (char **)malloc(sizeof(char*) * (words + 1));
	if (!ret)
		return (NULL);
	ret[words] = NULL;
	if (make_words(&ret, (char*)s, c) == 0)
	{
		i = 0;
		while (ret[i])
		{
			free(ret[i]);
			i++;
		}
		free(ret);
		return (NULL);
	}
	return (ret);
}
