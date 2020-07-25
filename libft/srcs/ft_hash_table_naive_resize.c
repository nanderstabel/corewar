/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hash_table_naive_resize.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 22:16:27 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/06 22:34:06 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_hash_table_naive_resize(t_hash_table *table, size_t add)
{
	size_t			index;
	t_elem			**tmp;

	if (table == NULL || add == 0)
		return (table);
	tmp = table->elem;
	table->size += add;
	table->elem = (t_elem **)ft_memalloc(sizeof(t_elem *) * table->size);
	index = 0;
	while (index < table->size - add)
	{
		if (tmp[index])
			ft_hash_table_add(table, tmp[index]->name, tmp[index]->content);
		++index;
	}
	free(tmp);
	return (table);
}
