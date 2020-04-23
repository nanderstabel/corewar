/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstfold.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/23 15:14:54 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/04/22 17:37:57 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	delete_beginning(t_list **alst, t_list *end)
{
	t_list	*curr;
	t_list	*tmp;

	curr = *alst;
	while (curr != end)
	{
		tmp = curr;
		curr = curr->next;
		ft_lstdelone(&tmp, &ft_delete);
	}
	*alst = end;
}

static void	real_lstfold(t_list **alst, t_list *start, t_list *end)
{
	t_list	*curr;
	t_list	*tmp;

	curr = *alst;
	while (curr)
	{
		if (curr->next == start)
			curr->next = end;
		curr = curr->next;
	}
	curr = start;
	while (curr != end)
	{
		tmp = curr;
		curr = curr->next;
		ft_lstdelone(&tmp, &ft_delete);
	}
}

void		ft_lstfold(t_list **alst, t_list *start, t_list *end)
{
	t_list	*curr;
	int		found;

	if (!alst || !(*alst) || !start)
		return ;
	curr = *alst;
	found = 0;
	while (curr)
	{
		if (curr == start)
			found = 1;
		if ((curr == end || !end) && found)
			found = 2;
		curr = curr->next;
	}
	if (found != 2)
		return ;
	if (start == *alst)
	{
		delete_beginning(alst, end);
		return ;
	}
	real_lstfold(alst, start, end);
}
