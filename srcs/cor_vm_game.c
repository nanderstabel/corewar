/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_vm_game.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 17:44:34 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/06/05 17:44:34 by mmarcell      ########   odam.nl         */
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
			assign_opcode(cursor);
		--(cursor->ctw);
		++(cursor->decay);
		cursor = cursor->next;
		if (cursor->ctw == 0)
			operations[convert_to_int(&(vm->arena[cursor->pc]), 1)](vm, cursor);
	}
	++(vm->cycle_count);
	++(vm->total_cycle_count);
	if (vm->cycle_count == CYCLE_TO_DIE)
		check_cursors(vm);
}
