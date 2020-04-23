/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 19:59:23 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/04/22 17:38:48 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	void	*ptr;
	size_t	i;

	ptr = NULL;
	i = 0;
	while (i < n)
	{
		if (*(((unsigned char*)s) + i) == (unsigned char)c)
		{
			ptr = &(*(((unsigned char*)s) + i));
			return (ptr);
		}
		i++;
	}
	return (ptr);
}
