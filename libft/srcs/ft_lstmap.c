/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/12 18:44:47 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/04/22 17:38:26 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*item;
	t_list	*head;

	head = NULL;
	while (lst)
	{
		item = f(lst);
		if (!item)
		{
			ft_lstdel(&(head), &(ft_delete));
			return (NULL);
		}
		ft_lstadd_back(&head, item);
		lst = lst->next;
	}
	return (head);
}
