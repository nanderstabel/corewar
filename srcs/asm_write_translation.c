/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_write_translation.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/07/06 16:42:28 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"






t_bool			write_translation(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;

	as->tmp = as->bytecode_list;
	while (as->tmp)
	{
		write(as->fd, as->tmp->content, as->tmp->content_size);
		as->tmp = as->tmp->next;
	}

	return (SUCCESS);	
}