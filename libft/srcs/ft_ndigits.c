/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ndigits.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 20:18:36 by nstabel       #+#    #+#                 */
/*   Updated: 2020/04/12 14:34:32 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_ndigits(long long nbr)
{
	size_t		n;
	long long	min;

	n = 0;
	min = -9223372036854775807;
	if (nbr < 0)
		nbr = -nbr;
	if (nbr < min)
		return (19);
	while (nbr)
	{
		nbr /= 10;
		++n;
	}
	return (n);
}
