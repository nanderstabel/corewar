/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_freezero.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/18 19:00:00 by nstabel       #+#    #+#                 */
/*   Updated: 2020/07/09 17:17:53 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freezero(void *mem, size_t size)
{
	ft_bzero(mem, size);
	ft_memdel(&mem);
	free(mem);
}
