/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_vm_game.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 17:44:34 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/13 13:31:29 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		game_loop(t_vm *vm, t_op_table operations)
{
	t_cursor	*cursor;

	cursor = vm->cursors;
	while (cursor != NULL)
	{
		if (cursor->ctw == 0)
		{
			cursor->op_code = convert_to_int(&(vm->arena[cursor->pc]), 1);
			if (cursor->op_code > 0 && cursor->op_code <= 16)
				cursor->ctw = g_op_tab[cursor->op_code - 1].cycles_to_wait;
			else
				cursor->pc = new_idx(cursor->pc, 1, FALSE);
		}
		if (cursor->ctw > 0)
			--(cursor->ctw);
		++(cursor->decay);
		if (cursor->ctw == 0 && cursor->op_code > 0 && cursor->op_code <= 16)
			operations[cursor->op_code](vm, cursor);
		cursor = cursor->next;
		if (vm->visualizer == TRUE)
			vis_print_data(vm);
	}
	++(vm->cycle_count);
	++(vm->total_cycle_count);
	if (vm->cycle_count == CYCLE_TO_DIE)
		perform_check(vm);
}
