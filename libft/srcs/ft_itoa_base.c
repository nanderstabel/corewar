/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/04 16:42:23 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/09 19:38:24 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** -------------------------------------------------------------------------- **
** converts an integer to a string - according to a given base
** only handles integer >= 0
** params
**	unsgnd long long n		integer to be converted to string
**	char base				the base according the integer needs to be converted
**	char is_cap				defines whether to capitalize letters in base 16
**	unsigned int len		the number of bytes of the finished string
** return
**	char *result			pointer to the created string
*/

char			*ft_itoa_base_unsgnd(unsigned long long int n, int base,
				int is_cap, unsigned int len)
{
	unsigned char			i;
	char					*result;
	unsigned long long int	power;

	result = (char *)malloc(sizeof(char) * len + 1);
	if (result == NULL)
		return (result);
	i = 0;
	while (i < len)
	{
		power = ft_power(base, len - i - 1);
		if (n / power < 10)
			result[i] = '0' + (n / power);
		else
			result[i] = is_cap ?
					('A' + (n / power) - 10) : ('a' + (n / power) - 10);
		n = n % power;
		++i;
	}
	return (result);
}

char			*ft_itoa_base(unsigned long long value, int base)
{
	char				*s;
	char				*hex;
	unsigned long long	tmp;
	int					i;

	i = 1;
	hex = "0123456789abcdef";
	tmp = value;
	while (tmp /= base)
		i++;
	s = (char *)malloc(sizeof(char) * i + 1);
	if (s == NULL)
		return (NULL);
	s[i] = 0;
	if (value == 0)
		s[0] = '0';
	while (value)
	{
		i--;
		s[i] = hex[value % base];
		value /= base;
	}
	return (s);
}
