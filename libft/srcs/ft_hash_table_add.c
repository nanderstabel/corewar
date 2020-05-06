/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hash_table_add.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 16:05:24 by nstabel       #+#    #+#                 */
/*   Updated: 2020/04/12 14:34:32 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_elem	*get_elem(char *name, size_t index, size_t hash, void *content)
{
	t_elem		*elem;

	elem = (t_elem *)ft_memalloc(sizeof(t_elem));
	elem->index = index;
	elem->hash = hash;
	elem->name = name;
	elem->content = content;
	return (elem);
}

static void		update_format(t_hash_table *hash_table, t_elem *elem)
{
	char		*hash;
	size_t		*name_width;
	size_t		*hash_width;
	size_t		hash_len;

	name_width = (size_t *)&(hash_table->width->next->next->address);
	hash_width = (size_t *)&(hash_table->width->next->next->next->address);
	hash = ft_itoa_base(elem->hash, 16);
	hash_len = ft_strlen(hash);
	elem->misc = ft_lstnew(hash, hash_len);
	free(hash);
	elem->body_content = ft_addr_lstnew(elem);
	if (ft_strlen(elem->name) + 4 > *name_width)
		*name_width = (size_t)ft_strlen(elem->name) + 4;
	ft_addr_lstapp(&elem->body_content, ft_addr_lstnew(elem->name));
	if (hash_len > *hash_width)
		*hash_width = hash_len;
	ft_addr_lstapp(&elem->body_content, ft_addr_lstnew(elem->misc->content));
}

static t_elem	*add_elem(t_hash_table *hash_table, t_elem *elem, size_t i)
{
	hash_table->elem[i] = elem;
	if (hash_table->format)
		update_format(hash_table, elem);
	return (elem);
}

t_elem			*ft_hash_table_add(t_hash_table *hash_table, char *key,
					void *content)
{
	size_t	i;
	size_t	probe;
	size_t	hash;

	hash = ft_hash(key);
	probe = 0;
	while (probe < hash_table->size)
	{
		i = (hash + probe) % hash_table->size;
		if (hash_table->elem[i])
		{
			if (hash_table->elem[i]->hash == hash)
				if (ft_strequ(hash_table->elem[i]->name, key))
				{
					free(content);
					return (NULL);
				}
		}
		else
			return (add_elem(hash_table, get_elem(key, i, hash, content), i));
		++probe;
	}
	return (NULL);
}
