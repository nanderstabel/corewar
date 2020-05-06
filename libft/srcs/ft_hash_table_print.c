/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hash_table_print.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 19:56:32 by nstabel       #+#    #+#                 */
/*   Updated: 2020/04/16 19:56:32 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_hash_table_print(t_hash_table *table, \
						void *(*columns)(t_hash_table *table))
{
	if (!table)
		return (NULL);
	ft_hash_table_update(table, columns);
	ft_puttbl(table);
	return (table);
}
