/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 20:03:19 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/04/22 17:43:23 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t n)
{
	size_t	i;
	size_t	hay_len;
	size_t	needle_len;

	i = 0;
	hay_len = ft_strlen(hay);
	needle_len = ft_strlen(needle);
	if (!(*needle))
		return ((char*)hay);
	if (!n || needle_len > hay_len || n < needle_len)
		return (NULL);
	while (i < (n - needle_len + 1) && i < (hay_len - needle_len + 1))
	{
		if (ft_strncmp(&(hay[i]), needle, needle_len) == 0)
			return (&(((char*)hay)[i]));
		i++;
	}
	return (NULL);
}
