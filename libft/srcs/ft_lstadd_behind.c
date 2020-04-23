/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_behind.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/23 17:28:29 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/04/22 17:36:53 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_behind(t_list **alst, t_list *node, t_list *new_nd)
{
	t_list	*curr;

	if (!alst || !(*alst) || !node || !new_nd)
		return ;
	curr = *alst;
	while (curr)
	{
		if (curr == node)
		{
			new_nd->next = node->next;
			node->next = new_nd;
			curr = new_nd;
			break ;
		}
		curr = curr->next;
	}
}
