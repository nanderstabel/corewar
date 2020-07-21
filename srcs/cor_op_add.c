/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_add.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 16:45:01 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/06/08 16:45:01 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	op_add_check(t_vm *vm, t_cursor *cursor)
{
	unsigned char	enc;
	enc = vm->arena[new_idx(cursor->pc, 1, 0)];
	if (get_arg_type(enc, 4) != 0 || \
		get_arg_type(enc, 3) != REG || \
		get_arg_type(enc, 2) != REG || \
		get_arg_type(enc, 1) != REG)
	{
		cursor->pc = new_idx(cursor->pc, 1, FALSE);
		return (ERROR);
	}
	else
		return (SUCCESS);
}

static int		get_value1(t_vm *vm, t_cursor *cursor, int type, int *size)
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
// int		op_ldi(t_vm *vm, t_cursor *cursor)
// {
// 	int		arg_1;
// 	int		arg_2;
// 	int		arg_3;
// 	int		size;
// 	if (op_ldi_check(vm, cursor) != SUCCESS)
// 		return (ERROR);
// 	size = 2;
// 	arg_1 = get_arg_type(vm->arena[new_idx(cursor->pc, 1, FALSE)], 1);
// 	arg_2 = get_arg_type(vm->arena[new_idx(cursor->pc, 1, FALSE)], 2);
// 	arg_1 = get_value(vm, cursor, arg_1, &size);
// 	arg_2 = get_value(vm, cursor, arg_2, &size);
// 	arg_3 = get_value(vm, cursor, REG, &size);
// 	if (arg_3 < REG_NUMBER)
// 		cursor->reg[arg_3] = convert_to_int(vm->arena, new_idx(cursor->pc, arg_1 + arg_2, 0), 4);;
// 	cursor->pc = new_idx(cursor->pc, size, FALSE);
// 	return (SUCCESS);
// }

int		op_add(t_vm *vm, t_cursor *cursor)
{
	int			arg_1;
	int			arg_2;
	int			arg_3;
	int			size;

	if (op_add_check(vm, cursor) != SUCCESS)
		return (ERROR);
	size = 2;




	if (vm == NULL || cursor == NULL)
		return (ERROR);
	return (SUCCESS);
}
