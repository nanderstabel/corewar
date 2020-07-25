/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_addr_lstsrt.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/15 15:47:33 by nstabel       #+#    #+#                 */
/*   Updated: 2020/03/15 15:47:33 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		partition(t_adlist *head, t_adlist **front, t_adlist **back)
{
	t_adlist		*fast;
	t_adlist		*slow;

	if (head == NULL || head->next == NULL)
	{
		*front = head;
		*back = NULL;
	}
	else
	{
		slow = head;
		fast = head->next;
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front = head;
		*back = slow->next;
		slow->next = NULL;
	}
}

static t_adlist	*merge(t_adlist *a, t_adlist *b, int (*method)(void *, void *))
{
	t_adlist		*ret;

	ret = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (method(a, b))
	{
		ret = a;
		ret->next = merge(a->next, b, method);
	}
	else
	{
		ret = b;
		ret->next = merge(a, b->next, method);
	}
	return (ret);
}

void			ft_addr_lstsrt(t_adlist **alst, int (*method)(void *, void *))
{
	t_adlist			*head;
	t_adlist			*a;
	t_adlist			*b;

	head = *alst;
	if (head == NULL)
		return ;
	if (head->next == NULL)
		return ;
	partition(head, &a, &b);
	ft_addr_lstsrt(&a, method);
	ft_addr_lstsrt(&b, method);
	*alst = merge(a, b, method);
}
