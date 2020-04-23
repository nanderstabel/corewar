/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strarrdel.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 14:05:52 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/04/10 17:35:49 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_strarrdel(char ***arr)
{
	int		i;

	if (arr == 0 || *arr == 0 || **arr == 0)
		return ;
	i = 0;
	while ((*arr)[i] != 0)
	{
		ft_strdel(&((*arr)[i]));
		++i;
	}
	free(*arr);
	*arr = 0;
}
