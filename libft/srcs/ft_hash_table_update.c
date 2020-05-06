/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hash_table_update.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/18 17:58:21 by nstabel       #+#    #+#                 */
/*   Updated: 2020/04/12 15:34:31 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_hash_table_update(t_hash_table *table, \
	void *(*columns)(t_hash_table *table))
{
	if (!table || !columns)
		return (NULL);
	if (table->mounted)
		if (ft_hash_table_drop(table, 4) == NULL)
			return (NULL);
	if (ft_hash_table_append(table, columns))
		return (table);
	return (NULL);
}
