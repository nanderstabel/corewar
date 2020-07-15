/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memrev.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/06 18:08:15 by nstabel       #+#    #+#                 */
/*   Updated: 2020/07/15 13:00:41 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memrev(void *src, size_t len)
{
	size_t			index;
	void			*start;
	void			*end;
	unsigned char	c;

	if (!src)
		return (src);
	index = 0;
	start = src;
	end = src + (len - 1);
	while (index < len)
	{
		c = *((unsigned char*)start);
		*((unsigned char*)start) = *((unsigned char*)end);
		*((unsigned char*)end) = c;
		start++;
		end--;
		index++;
		len--;
	}
	return (src);
}
