/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strndup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgross <mgross@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/20 10:41:15 by mgross        #+#    #+#                 */
/*   Updated: 2020/04/12 14:34:32 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** This function duplicates n number of bytes from src and returns a string. If
** src is smaller then len, it will fill the rest up with deliminating zeros.
*/

char	*ft_strndup(const char *src, size_t len)
{
	char	*str;

	if (len <= 0)
		return (NULL);
	if (src == NULL)
		return (NULL);
	str = ft_strnew(len);
	if (str == NULL)
		return (NULL);
	ft_strncpy(str, src, len);
	return (str);
}
