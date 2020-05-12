/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_wspace_strequ.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 17:10:29 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/12 20:31:26 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_wspace_strequ(const char *s1, const char *s2)
{
	size_t		index;

	index = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[index] != ' ' && s1[index] != '\f' && s1[index] != '\v' &&
	s1[index] != '\n' && s1[index] != '\0')
	{
		index++;
	}
	if (s1[index] == '\0')
		return (0);
	if (ft_strncmp(s1, s2, index) == 0)
		return (1);
	return (0);
}
