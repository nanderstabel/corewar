/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 20:12:13 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/04/22 17:36:38 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** -------------------------------------------------------------------------- **
** converts an integer to a string - also handles negative numbers and thus
** is base 10
** params
**	long long int n		integer to be converted to string
** return
**	char *result		pointer to the created string
*/

char		*ft_itoa(long long int n)
{
	char					*result;
	unsigned int			len;
	unsigned long long int	power;
	unsigned int			i;

	len = ft_absolute_nbrlen(n, 10) + (n < 0);
	if (n == -9223372036854775807)
		return ("-9223372036854775807");
	result = (char *)malloc(sizeof(char) * len + 1);
	if (result == NULL)
		return (result);
	result[0] = n < 0 ? '-' : '0';
	i = (n < 0);
	n = (n < 0) ? -n : n;
	result[len] = '\0';
	while (i < len)
	{
		power = ft_power(10, len - i - 1);
		result[i] = '0' + (n / power);
		n = n % power;
		++i;
	}
	return (result);
}
