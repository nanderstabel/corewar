/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_addr_lstdel.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/09 19:54:06 by nstabel       #+#    #+#                 */
/*   Updated: 2020/04/07 09:30:24 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_addr_lstdel(t_adlist **alst)
{
	t_adlist	*tmp;

	while (*alst)
	{
		tmp = *alst;
		ft_addr_lstdelone(&tmp);
		*alst = (*alst)->next;
	}
	ft_memdel((void **)alst);
}
