/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_and.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 16:47:10 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/24 14:55:51 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	op_and_check(t_vm *vm, t_cursor *cursor)
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

int		op_and(t_vm *vm, t_cursor *cursor)
{
	//ft_printf("pc: %i, xor, cycle: %i\n", cursor->pc, vm->total_cycle_count);

	int		params[4];

	if (op_and_check(vm, cursor) != SUCCESS)
		return (ERROR);
	params[0] = 2;
	params[1] = get_arg_type(vm->arena[new_idx(cursor->pc, 1, FALSE)], 1);
	params[2] = get_arg_type(vm->arena[new_idx(cursor->pc, 1, FALSE)], 2);

	if (get_value(vm, cursor, params) == SUCCESS)
	{
		params[3] = convert_to_int(vm->arena, new_idx(cursor->pc, params[0], 0), 1);

		if (params[3] > 0 && params[3] <= REG_NUMBER)
			cursor->reg[params[3]] = (params[1] & params[2]);
		params[0]++;
		cursor->carry = (cursor->reg[params[3]]) ? 0 : 1;
	}
	cursor->pc = new_idx(cursor->pc, params[0], FALSE);
	return (SUCCESS);
}


// int		op_and(t_vm *vm, t_cursor *cursor)
// {
// 	//ft_printf("pc: %i, and, cycle: %i\n", cursor->pc, vm->total_cycle_count);
// 	int		arg_1;
// 	int		arg_2;
// 	int		arg_3;

// 	if (op_and_check(vm, cursor) != SUCCESS)
// 		return (ERROR);
// 	arg_1 = convert_to_int(vm->arena, new_idx(cursor->pc, 2, 0), 1);
// 	arg_2 = convert_to_int(vm->arena, new_idx(cursor->pc, 3, 0), 1);
// 	arg_3 = convert_to_int(vm->arena, new_idx(cursor->pc, 4, 0), 1);
// 	if (0 < arg_1 && arg_1 <= REG_NUMBER && 
// 		0 < arg_2 && arg_2 <= REG_NUMBER && 
// 		0 < arg_3 && arg_3 <= REG_NUMBER)
// 	{
// 		cursor->reg[arg_3] = cursor->reg[arg_1] & cursor->reg[arg_2];
// 		cursor->carry = (cursor->reg[arg_3]) ? 0 : 1;
// 	}
// 	cursor->pc = new_idx(cursor->pc, 5, FALSE);
// 	return (SUCCESS);
// }
