/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_zjmp.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 16:52:34 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/23 16:40:38 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		op_zjmp(t_vm *vm, t_cursor *cursor)
{
	//ft_printf("pc: %i, zjmp, cycle: %i\n", cursor->pc, vm->total_cycle_count);
	int		arg;

	arg = convert_to_int(vm->arena, new_idx(cursor->pc, 1, FALSE), 2);
	if (cursor->carry)
		cursor->pc = new_idx(cursor->pc, arg, FALSE);
	else
		cursor->pc = new_idx(cursor->pc, 3, FALSE);
	return (SUCCESS);
}
