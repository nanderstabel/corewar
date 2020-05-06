/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hash_table_get.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 16:21:24 by nstabel       #+#    #+#                 */
/*   Updated: 2020/04/14 11:22:32 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_elem	*ft_hash_table_get(t_hash_table *hash_table, char *key)
{
	size_t	i;
	size_t	hash;
	size_t	probe;

	hash = ft_hash(key);
	probe = 0;
	while (probe < hash_table->size)
	{
		i = (hash + probe) % hash_table->size;
		if (hash_table->elem[i])
			if (hash_table->elem[i]->hash == hash)
				if (ft_strequ(hash_table->elem[i]->name, key))
					return (hash_table->elem[i]);
		++probe;
	}
	return (NULL);
}
