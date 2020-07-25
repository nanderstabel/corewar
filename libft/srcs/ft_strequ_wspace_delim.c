/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strequ_wspace_delim.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 16:33:33 by zitzak        #+#    #+#                 */
/*   Updated: 2020/07/09 19:35:37 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ_wspace_delim(const char *s1, const char *s2)
{
	size_t		index;

	index = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[index] != ' ' && s1[index] != '\f' && s1[index] != '\v' &&
	s1[index] != '\n' && s1[index] != '\0' && s1[index] != '\t' &&
	s1[index] != '\"')
	{
		index++;
	}
	if (ft_strncmp(s1, s2, index) == 0)
		return (1);
	return (0);
}
