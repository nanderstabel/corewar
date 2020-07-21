/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_ld.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 16:47:57 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/17 15:14:01 by nstabel       ########   odam.nl         */
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

int		op_ld(t_vm *vm, t_cursor *cursor)
{
	int		arg_1;
	int		arg_2;
	int		size;

	if (op_ld_check(vm, cursor) != SUCCESS)
		return (ERROR);
	size = 2;
	arg_1 = get_arg_type(vm->arena[new_idx(cursor->pc, 1, FALSE)], 1);
	// ft_printf("[arg_1 = %u, size = %u]\n", arg_1, size);
	arg_1 = get_value(vm, cursor, arg_1, &size);
	// ft_printf("[arg_1 = %u, size = %u]\n", arg_1, size);
	arg_2 = convert_to_int(vm->arena, new_idx(cursor->pc, size, 0), 1);
	// ft_printf("[arg_1 = %u, arg_2 = %u, size = %u]\n", arg_1, arg_2, size);
	if (arg_2 > 0 && arg_2 < REG_NUMBER)
		cursor->reg[arg_2] = arg_1;
	else
		return (ERROR);
	size++;
	cursor->pc = new_idx(cursor->pc, size, FALSE);
	cursor->carry = (arg_1) ? 0 : 1;
	return (SUCCESS);
}
