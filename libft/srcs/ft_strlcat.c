/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 20:01:46 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/04/22 17:42:30 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	left;
	size_t	len_dst;
	size_t	len_src;

	left = size;
	len_dst = 0;
	len_src = ft_strlen(src);
	while (left != 0 && dst[len_dst] != 0)
	{
		left--;
		len_dst++;
	}
	if (left == 0)
		return (size + len_src);
	i = 0;
	while (left > 1 && src[i])
	{
		dst[len_dst + i] = src[i];
		left--;
		i++;
	}
	dst[len_dst + i] = 0;
	return (len_dst + len_src);
}
