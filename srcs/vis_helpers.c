/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vis_helpers.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 15:47:10 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/06 16:30:23 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

char	*vis_itoa(unsigned char nbr)
{
	char	*result;

	result = ft_strnew(2);
	if (nbr < 15)
		result[0] = '0';
	else
	{
		if (nbr / 16 < 10)
			result[0] = '0' + nbr / 16;
		else
			result[0] = 'a' + nbr / 16 - 10;
	}
	if (nbr % 16 < 10)
		result[1] = '0' + nbr % 16;
	else
		result[1] = 'a' + nbr % 16 - 10;
	return (result);
}

void	vis_putnbr(unsigned char nbr)
{
	char	*result;

	result = vis_itoa(nbr);
	//print number with visualizer
	ft_strdel(&result);
}
