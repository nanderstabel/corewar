/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_absolute_nbrlen.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/20 15:15:53 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/04/22 17:53:09 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_absolute_nbrlen(long long int nbr, int base)
{
	unsigned int nbrlen;

	nbrlen = 1;
	while ((nbr <= (-1) * base || base <= nbr))
	{
		nbr = nbr / base;
		++nbrlen;
	}
	return (nbrlen);
}
