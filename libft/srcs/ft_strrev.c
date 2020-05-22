/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrev.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 18:53:21 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/05/20 18:53:21 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char			*tmp;
	unsigned int	i;
	unsigned int	j;

	tmp = ft_strdup(str);
	i = ft_strlen(str);
	j = 0;
	while (i != 0)
	{
		str[j] = tmp[i];
		j += 1;
		i -= 1;
	}
	ft_strdel(&tmp);
	return (str);
}
