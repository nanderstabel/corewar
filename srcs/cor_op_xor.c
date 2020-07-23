/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_xor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 16:52:21 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/23 18:50:36 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	op_xor_check(t_vm *vm, t_cursor *cursor)
{
	unsigned char	enc;

	enc = vm->arena[new_idx(cursor->pc, 1, 0)];
	if (get_arg_type(enc, 4) != 0 || \
		get_arg_type(enc, 3) != REG || \
		get_arg_type(enc, 2) == 0 || \
		get_arg_type(enc, 1) == 0)
		return (ERROR);
	else
		return (SUCCESS);
}

static int		get_value(t_vm *vm, t_cursor *cursor, int type, int *size)
{
	if (type == REG)
	{
		type = convert_to_int(vm->arena, new_idx(cursor->pc, *size, 0), 1);
		type = cursor->reg[type];
		*size += 1;
	}
	else if (type == IND)
	{
		type = convert_to_int(vm->arena, new_idx(cursor->pc, *size, 0), 2);
		type = convert_to_int(vm->arena, new_idx(cursor->pc, type, 0), 4);
		*size += 2;
	}
	else if (type == DIR)
	{
		type = convert_to_int(vm->arena, new_idx(cursor->pc, *size, 0), 4);
		*size += 4;
	}
	return (type);
}

int		op_xor(t_vm *vm, t_cursor *cursor)
{
	//ft_printf("pc: %i, xor, cycle: %i\n", cursor->pc, vm->total_cycle_count);
	int		arg_1;
	int		arg_2;
	int		arg_3;
	int		size;

	if (op_xor_check(vm, cursor) != SUCCESS)
		return (ERROR);
	size = 2;
	arg_1 = get_arg_type(vm->arena[new_idx(cursor->pc, 1, FALSE)], 1);
	arg_2 = get_arg_type(vm->arena[new_idx(cursor->pc, 1, FALSE)], 2);

	arg_1 = get_value(vm, cursor, arg_1, &size);
	arg_2 = get_value(vm, cursor, arg_2, &size);
	arg_3 = convert_to_int(vm->arena, new_idx(cursor->pc, size, 0), 1);

	if (arg_3 > 0 && arg_3 <= REG_NUMBER)
		cursor->reg[arg_3] = (arg_1 ^ arg_2);
	size++;
	cursor->pc = new_idx(cursor->pc, size, FALSE);
	cursor->carry = (cursor->reg[arg_3]) ? 0 : 1;
	return (SUCCESS);
}
