/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_live.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 11:20:48 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/10 16:29:16 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

//TODO: double check whether an invalid argument for live (when the id doesn't match a player) does.

static void	vis_live(t_vm *vm, t_cursor *cursor)
{
	if (vm->vis == NULL)
		return ;
	vm->vis->attr[cursor->player](vis_calc_att(0, 1), vm->vis->graphics->arena);
	vm->vis->index = cursor->pc;
	vm->vis->bytes = 1;
	vis_print_cursor(vm->vis);
}

void	op_live(t_vm *vm, t_cursor *cursor)
{
	int				arg;

	arg = convert_to_int(&(vm->arena[new_idx(cursor->pc, 1, FALSE)]), 4);
	if (0 < -arg && (unsigned int)-arg <= vm->champ_count)
	{
		vm->last_live = arg;
		++(vm->live_count);
		cursor->decay = 0;
		if (vm->vis == NULL)
			ft_printf("A process shows that player %d (%s) is alive\n", \
				-arg, vm->champ[-arg]->header.prog_name);
		vis_live(vm, cursor);
		move_pc(vm, cursor, 5);
		// If wanted live count for champ
		return ;
	}
	else
		move_pc(vm, cursor, 1);
	return ;
}
