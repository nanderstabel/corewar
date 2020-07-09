/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_hash_table.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 13:40:07 by nstabel       #+#    #+#                 */
/*   Updated: 2020/07/09 17:01:47 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		free_elements(t_hash_table *table, void (*free_content)(void *))
{
	t_elem	**elem;
	size_t	i;

	elem = table->elem;
	i = 0;
	while (i < table->size)
	{
		if (elem[i])
		{
			ft_strdel(&elem[i]->name);
			if (free_content)
				free_content(elem[i]->content);
			ft_addr_lstdel(&elem[i]->body_content);
			if (elem[i]->misc)
				ft_lstdel(&elem[i]->misc, ft_freezero);
			free(elem[i]);
		}
		++i;
	}
}

static void		free_formats(t_hash_table *table)
{
	ft_lstdel(&table->header_format, ft_freezero);
	ft_lstdel(&table->header_content, ft_freezero);
	ft_lstdel(&table->body_format, ft_freezero);
	ft_addr_lstdel(&table->width);
	ft_strdel(&table->format);
}

void			ft_free_hash_table(t_hash_table **table,
					void (*free_content)(void *))
{
	if (!*table)
		return ;
	free_elements(*table, free_content);
	if ((*table)->format)
		free_formats(*table);
	ft_strdel(&(*table)->title);
	free((*table)->elem);
	free(*table);
	*table = NULL;
}
