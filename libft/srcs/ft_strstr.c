/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 20:02:57 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/04/22 17:43:38 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *hay, const char *needle)
{
	size_t	i;
	size_t	hay_len;
	size_t	needle_len;

	i = 0;
	hay_len = ft_strlen(hay);
	needle_len = ft_strlen(needle);
	if (needle_len > hay_len)
		return (NULL);
	while (i <= hay_len - needle_len)
	{
		if (ft_strncmp(&(hay[i]), needle, needle_len) == 0)
			return (&(((char *)hay)[i]));
		i++;
	}
	return (NULL);
}
