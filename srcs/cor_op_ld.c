/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_ld.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 16:47:57 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/24 18:34:37 by nstabel       ########   odam.nl         */
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
		return (ERROR);
	else
		return (SUCCESS);
}

int		op_ld(t_vm *vm, t_cursor *cursor)
{
	int		params[4];

	if (op_ld_check(vm, cursor) != SUCCESS)
		return (ERROR);
	params[0] = 2;
	params[1] = get_arg_type(vm->arena[new_idx(cursor->pc, 1, FALSE)], 1);
	if (get_value(vm, cursor, params) == SUCCESS)
	{
		params[2] = convert_to_int(vm->arena, new_idx(cursor->pc, params[0], 0), 1);
		if (params[2] > 0 && params[2] <= REG_NUMBER)
			cursor->reg[params[2]] = params[1];
		params[0]++;
		cursor->carry = (cursor->reg[params[2]]) ? 0 : 1;
		ft_printf("ld| arg1: %i, arg2: %i, carry: %i\n", params[1], params[2], cursor->carry);
	}
	cursor->pc = new_idx(cursor->pc, params[0], FALSE);
	return (SUCCESS);
}
