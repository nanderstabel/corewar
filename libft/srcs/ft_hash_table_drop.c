/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hash_table_drop.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/12 15:31:46 by nstabel       #+#    #+#                 */
/*   Updated: 2020/04/15 17:22:43 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		cut_list(t_list *row, size_t cutoff)
{
	size_t		index;

	index = 1;
	while (index < cutoff)
	{
		row = row->next;
		++index;
	}
	ft_lstdel(&row->next, ft_freezero);
	row->next = NULL;
}

static void		cut_adlist(t_adlist *row, size_t cutoff)
{
	size_t		index;

	index = 1;
	while (index < cutoff)
	{
		row = row->next;
		++index;
	}
	ft_addr_lstdel(&row->next);
	row->next = NULL;
}

static void		shift(t_hash_table *table)
{
	t_adlist	*last_width;

	last_width = table->width;
	while (last_width->next)
		last_width = last_width->next;
	last_width->address -= 2;
}

void			*ft_hash_table_drop(t_hash_table *table, size_t cutoff)
{
	size_t		index;
	t_elem		*elem;

	if (!table || cutoff < 4)
		return (NULL);
	cut_list(table->header_content, cutoff);
	cut_list(table->header_format, cutoff);
	cut_list(table->body_format, cutoff);
	cut_adlist(table->width, cutoff);
	index = 0;
	while (index < table->size)
	{
		if (table->elem[index])
		{
			elem = table->elem[index];
			cut_adlist(elem->body_content, cutoff - 1);
		}
		++index;
	}
	if (cutoff == 4)
		table->mounted = 0;
	shift(table);
	return (table);
}
