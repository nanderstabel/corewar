/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_malloc_hash_table.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 16:07:55 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/06 22:18:45 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		add_header(t_hash_table **hash_table, char *format)
{
	size_t	len;

	len = ft_strlen(format);
	(*hash_table)->header_format = ft_lstnew(format, len);
	ft_lstadd(&(*hash_table)->header_format, ft_lstnew(format, len));
	ft_lstadd(&(*hash_table)->header_format, ft_lstnew(format, len));
	ft_lstadd(&(*hash_table)->header_format, ft_lstnew("%-*s", 4));
	(*hash_table)->header_content = ft_lstnew("hash", 4);
	ft_lstadd(&(*hash_table)->header_content, ft_lstnew("name", 4));
	ft_lstadd(&(*hash_table)->header_content, ft_lstnew("address  ", 9));
	ft_lstadd(&(*hash_table)->header_content, ft_lstnew("index", 5));
}

static void		add_body(t_hash_table **hash_table, char *format)
{
	size_t	len;

	len = ft_strlen(format);
	(*hash_table)->body_format = ft_lstnew(format, len);
	ft_lstadd(&(*hash_table)->body_format, ft_lstnew(format, len));
	ft_lstadd(&(*hash_table)->body_format, ft_lstnew("%-*p", 4));
	ft_lstadd(&(*hash_table)->body_format, ft_lstnew("[%*i] --> ", 10));
}

static void		add_width(t_hash_table **hash_table)
{
	size_t		len;

	len = ft_ndigits((*hash_table)->size - 1) + 7;
	(*hash_table)->width = ft_addr_lstnew((void *)4);
	ft_addr_lstadd(&(*hash_table)->width, ft_addr_lstnew((void *)8));
	ft_addr_lstadd(&(*hash_table)->width, ft_addr_lstnew((void *)16));
	ft_addr_lstadd(&(*hash_table)->width, ft_addr_lstnew((void *)len));
}

static void		add_formats(t_hash_table **hash_table, char *format)
{
	if (format == NULL)
		return ;
	add_header(hash_table, format);
	add_body(hash_table, format);
	add_width(hash_table);
}

t_hash_table	*ft_malloc_hash_table(size_t size, char *title, char *format)
{
	t_hash_table	*hash_table;

	if (!size)
		return (NULL);
	hash_table = (t_hash_table *)ft_memalloc(sizeof(t_hash_table));
	if (hash_table == NULL)
		return (NULL);
	hash_table->elem = (t_elem **)ft_memalloc(sizeof(t_elem *) * size);
	if (hash_table->elem == NULL)
		return (NULL);
	hash_table->title = ft_strdup(title);
	if (format)
		hash_table->format = ft_strdup(format);
	hash_table->size = size;
	add_formats(&hash_table, format);
	return (hash_table);
}
