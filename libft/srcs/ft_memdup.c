/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/15 18:33:29 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/04/22 17:39:08 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(void *ptr, size_t size)
{
	void	*ret;
	size_t	i;

	i = 0;
	if (!ptr || !size)
		return (NULL);
	ret = ft_memalloc(size);
	if (!ret)
		return (NULL);
	while (i < size)
	{
		((char*)ret)[i] = ((char*)ptr)[i];
		i++;
	}
	return (ret);
}
