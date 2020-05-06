/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hash_table_append.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/07 12:28:27 by nstabel       #+#    #+#                 */
/*   Updated: 2020/04/12 15:21:39 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_hash_table_append(t_hash_table *table, \
	void *(*columns)(t_hash_table *table))
{
	t_adlist	*last_width;

	if (table == NULL || columns == NULL)
		return (NULL);
	last_width = table->width;
	while (last_width->next)
		last_width = last_width->next;
	last_width->address += 2;
	if (columns(table))
	{
		table->mounted = 1;
		return (table);
	}
	return (NULL);
}
