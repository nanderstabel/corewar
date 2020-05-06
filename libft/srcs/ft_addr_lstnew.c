/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_addr_lstnew.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/08 12:23:32 by nstabel       #+#    #+#                 */
/*   Updated: 2020/04/12 14:34:32 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_adlist	*ft_addr_lstnew(void *address)
{
	t_adlist	*list;

	list = (t_adlist *)malloc(sizeof(t_adlist));
	if (list == NULL)
		return (NULL);
	list->address = address;
	list->next = NULL;
	return (list);
}
