/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 20:11:37 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/04/22 17:43:48 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s)
{
	char	*ret;
	size_t	start;
	size_t	end;

	if (!s)
		return (NULL);
	start = 0;
	end = ft_strlen(s);
	while (s[start] &&
			(s[start] == ' ' || s[start] == '\t' || s[start] == '\n'))
		start++;
	while (end > 0 &&
			(s[end - 1] == ' ' || s[end - 1] == '\t' || s[end - 1] == '\n'))
		end--;
	if (end < start)
		end = start;
	ret = ft_strsub(s, start, (end - start));
	return (ret);
}
