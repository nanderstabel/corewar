/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nchar.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgross <mgross@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/21 16:43:50 by mgross        #+#    #+#                 */
/*   Updated: 2020/04/12 14:34:32 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** This function searches for the char c in string str. If it find the char it
** returns the count (incl. the char) in intgers (starting at 1 not 0). If he
** doesnt find c then it returnes a 0.
*/

int		ft_nchar(const char *str, int c)
{
	size_t	count;

	count = 0;
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (*str == ((unsigned char)c))
		{
			return (count + 1);
		}
		count++;
		str++;
	}
	return (0);
}
