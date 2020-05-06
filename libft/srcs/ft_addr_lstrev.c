/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_addr_lstrev.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/20 13:57:24 by nstabel       #+#    #+#                 */
/*   Updated: 2020/03/20 13:57:24 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_adlist				*ft_addr_lstrev(t_adlist *alst)
{
	t_adlist	*a;
	t_adlist	*b;

	if (!alst)
		return (NULL);
	a = alst;
	while (a->next)
	{
		b = alst;
		alst = a->next;
		a->next = alst->next;
		alst->next = b;
	}
	return (alst);
}
