/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_ld.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 16:47:57 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/15 21:26:22 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// If Argument2 is of type T_REG, set value from registry <Argument1> into registry <Argument2>
// If Argument2 is of type T_IND, set value from registry <Argument1> into memory. 
// Address is calculated as follows: (current_position + (Argument2 % IDX_MOD))

// REG 01	1	Registry Rx (where х = registry number, 1 to REG_NUMBER)			
// DIR 10	2-4	A number, saved on 2 or 4 bytes, depending on label			
// IND 11	2	Relative address, read 4 bytes from position <±T_IND bytes>

// 01010000
static int	op_ld_check(t_vm *vm, t_cursor *cursor)
{
	unsigned char	enc;

	enc = vm->arena[new_idx(cursor->pc, 1, 0)];
	if (get_arg_type(enc, 4) != 0 || \
		get_arg_type(enc, 3) != 0 || \
		get_arg_type(enc, 2) != REG || \
		get_arg_type(enc, 1) == 0 ||
		get_arg_type(enc, 1) == REG)
	{
		cursor->pc = new_idx(cursor->pc, 1, FALSE);
		return (ERROR);
	}
	else
		return (SUCCESS);
}

int		op_ld(t_vm *vm, t_cursor *cursor)
{
	int		arg_1;
	int		arg_2;
	int		type;

	if (op_ld_check(vm, cursor) != SUCCESS)
		return (ERROR);
	type = get_arg_type(vm->arena[new_idx(cursor->pc, 1, FALSE)], 1);
	if (type == DIR)
	{
		arg_1 = convert_to_int(vm->arena, new_idx(cursor->pc, 2, 0), 4);
		arg_2 = convert_to_int(vm->arena, new_idx(cursor->pc, 6, 0), 1);
		if (arg_2 < REG_NUMBER)
			cursor->reg[arg_2] = arg_1;
		cursor->pc = new_idx(cursor->pc, 7, FALSE);
	}
	else if (type == IND)
	{
		arg_1 = convert_to_int(vm->arena, new_idx(cursor->pc, 2, 0), 2);
		arg_1 = convert_to_int(vm->arena, new_idx(cursor->pc, arg_1, 0), 4);
		arg_2 = convert_to_int(vm->arena, new_idx(cursor->pc, 4, 0), 1);
		if (arg_2 < REG_NUMBER)
			cursor->reg[arg_2] = arg_1;
		cursor->pc = new_idx(cursor->pc, 5, FALSE);
	}
	cursor->carry = (arg_1) ? 0 : 1;
	return (SUCCESS);
}
