/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_or.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 16:50:13 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/23 16:40:38 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	op_or_check(t_vm *vm, t_cursor *cursor)
{
	unsigned char	enc;

	enc = vm->arena[new_idx(cursor->pc, 1, 0)];
	if (get_arg_type(enc, 4) != 0 || \
		get_arg_type(enc, 3) != REG || \
		get_arg_type(enc, 2) == 0 || \
		get_arg_type(enc, 1) == 0)		return (ERROR);
	else
		return (SUCCESS);
}

// static int		get_value(t_vm *vm, t_cursor *cursor, int type, int *size)
// {
// 	if (type == REG)
// 	{
// 		type = convert_to_int(vm->arena, new_idx(cursor->pc, *size, 0), 1);
// 		type = cursor->reg[type];
// 		*size += 1;
// 	}
// 	else if (type == IND)
// 	{
// 		type = convert_to_int(vm->arena, new_idx(cursor->pc, *size, 0), 2);
// 		type = convert_to_int(vm->arena, new_idx(cursor->pc, type, 0), 4);
// 		*size += 2;
// 	}
// 	else if (type == DIR)
// 	{
// 		type = convert_to_int(vm->arena, new_idx(cursor->pc, *size, 0), 4);
// 		*size += 4;
// 	}
// 	return (type);
// }

int		op_or(t_vm *vm, t_cursor *cursor)
{
	//ft_printf("pc: %i, or, cycle: %i\n", cursor->pc, vm->total_cycle_count);
	int		arg_1;
	int		arg_2;
	int		arg_3;

	if (op_add_check(vm, cursor) != SUCCESS)
		return (ERROR);
	arg_1 = convert_to_int(vm->arena, new_idx(cursor->pc, 2, 0), 1);
	arg_2 = convert_to_int(vm->arena, new_idx(cursor->pc, 3, 0), 1);
	arg_3 = convert_to_int(vm->arena, new_idx(cursor->pc, 4, 0), 1);
	if (0 < arg_1 && arg_1 <= REG_NUMBER && \
		0 < arg_2 && arg_2 <= REG_NUMBER && \
		0 < arg_3 && arg_3 <= REG_NUMBER)
	{
		cursor->reg[arg_3] = cursor->reg[arg_1] | cursor->reg[arg_2];
		cursor->carry = (cursor->reg[arg_3]) ? 0 : 1;
	}
	cursor->pc = new_idx(cursor->pc, 5, FALSE);
	return (SUCCESS);
}
