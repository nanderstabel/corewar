/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_live.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 11:20:48 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/06/02 11:20:48 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

//TODO: double check whether an invalid arument for live (when the id doesn't match a player) does.

void	op_live(t_vm *vm, t_cursor *cursor)
{
	int				arg;

	arg = convert_to_int(vm->arena[new_idx(cursor->pc, 1, FALSE)], 4);
	if (0 < -arg && -arg <= MAX_PLAYERS && \
		vm->champ[-arg] != NULL)
	{
		vm->last_live = arg;
		++(vm->live_count);
		cursor->decay = 0;
		ft_printf("A process shows that player %d (%s) is alive\n", \
			-arg, vm->champ[-arg]->header.prog_name);
		//call visualizer
		cursor->pc = new_idx(cursor->pc, 5, FALSE);
		return ;
	}
	cursor->pc = new_idx(cursor->pc, 1, FALSE);
	return ;
}
