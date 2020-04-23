/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsub.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 20:11:00 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/04/22 17:43:44 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ret;
	size_t	len_s;

	i = 0;
	len_s = 0;
	if (s)
		len_s = ft_strlen(s);
	ret = ft_strnew(len);
	if (!ret)
		return (NULL);
	while (start < len_s && i < len)
	{
		if (start + i < len_s)
			ret[i] = ((char*)s)[start + i];
		i++;
	}
	return (ret);
}
