/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hash.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 10:06:46 by nstabel       #+#    #+#                 */
/*   Updated: 2020/04/12 15:21:20 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				ft_hash(char *key)
{
	size_t	index;
	size_t	hash;

	index = 0;
	hash = 0;
	while (key[index])
	{
		hash += (key[index] * (key[index] - 1) * (key[index] - 2) * \
			(key[index] - 3)) * (index + 1);
		++index;
	}
	hash *= index;
	return (hash);
}
