/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_label_columns.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 13:14:27 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/15 13:48:13 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vertex_columns.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 17:27:12 by nstabel       #+#    #+#                 */
/*   Updated: 2020/04/15 17:33:06 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void			add_body_content(t_hash_table *table)
{
	t_elem		*elem;
	size_t		i;

	i = 0;
	while (i < table->size)
	{
		if (table->elem[i])
		{
			elem = table->elem[i];
			ft_lstadd(&elem->misc, ft_lstnew(ft_itoa((long long)elem->content), ft_ndigits((long long)elem->content)));
			ft_addr_lstapp(&elem->body_content, ft_addr_lstnew(elem->misc->content));
		}
		++i;
	}
}

void				*label_columns(t_hash_table *table)
{
	if (table == NULL)
		return (NULL);
	ft_lstadd_back(&table->header_content, ft_lstnew("address", 7));
	ft_lstadd_back(&table->header_format, ft_lstnew(table->format, 4));
	ft_lstadd_back(&table->body_format, ft_lstnew(table->format, 4));
	add_body_content(table);
	ft_addr_lstapp(&table->width, ft_addr_lstnew((void *)8));
	return (table);
}
