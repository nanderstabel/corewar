/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 20:00:16 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/04/22 17:42:04 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	size_t	i;

	if (s == 0)
		return (0);
	ret = ft_strnew(ft_strlen(s));
	if (ret != 0 && s != 0)
	{
		i = 0;
		while (s[i])
		{
			((unsigned char*)ret)[i] = ((unsigned char*)s)[i];
			i++;
		}
		((unsigned char*)ret)[i] = ((unsigned char*)s)[i];
	}
	return (ret);
}
