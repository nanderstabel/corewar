/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_before.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/23 17:28:34 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/04/22 17:36:48 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_before(t_list **alst, t_list *node, t_list *new_nd)
{
	t_list	*curr;

	if (!alst || !(*alst) || !new_nd)
		return ;
	if (*alst == node)
	{
		ft_lstadd(alst, new_nd);
		return ;
	}
	if (!node)
		ft_lstadd_back(alst, new_nd);
	curr = *alst;
	while (curr)
	{
		if (curr->next == node)
		{
			curr->next = new_nd;
			new_nd->next = node;
			return ;
		}
		curr = curr->next;
	}
}
