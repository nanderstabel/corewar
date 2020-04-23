/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_absolute_doublelen.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/22 13:21:17 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/04/22 17:34:01 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_absolute_doublelen(long double ld, unsigned int prcs)
{
	unsigned int	len;

	if (ld < 0)
		ld = -ld;
	if (ld < ft_ldouble_power(10, 300))
	{
		len = 1;
		while (len < 301 && ft_ldouble_power(10, len) <= ld)
			++len;
	}
	else if (ld < ft_ldouble_power(10, 4000))
	{
		len = 301;
		while (len < 4001 && ft_ldouble_power(10, len) <= ld)
			++len;
	}
	else
	{
		len = 4001;
		while (len < 4933 && ft_ldouble_power(10, len) <= ld)
			++len;
	}
	return (len + (prcs > 0) + prcs);
}
