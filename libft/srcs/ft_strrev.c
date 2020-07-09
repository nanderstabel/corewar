/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrev.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/06 18:08:15 by nstabel       #+#    #+#                 */
/*   Updated: 2020/07/09 19:36:14 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char			*start;
	char			*end;
	char			c;

	if (str)
	{
		start = str;
		end = str + (ft_strlen(str) - 1);
		while (start < end)
		{
			c = *start;
			*start = *end;
			*end = c;
			start++;
			end--;
		}
	}
	return (str);
}
