/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_sti.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/13 15:10:22 by lhageman      #+#    #+#                 */
/*   Updated: 2020/07/13 17:05:22 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
// "Value from the Argument1 is written to the memory, to the address: current_position + 
// ((Argument2 + Argument3) % IDX_MOD)
// If Argument2 is of type T_IND, value (4 bytes) for address calculation is read from 
// memory: current_position + (Argument2 % IDX_MOD)"							
// 11	sti	[T_REG]	[T_REG | T_DIR | T_IND]	[T_REG | T_DIR]	[00001011]	[0x0B]	store index ctw:25

static int	get_arg_2_value(t_vm *vm, t_cursor *cursor, int *value)
{
	int				type;
	unsigned char	enc;
	unsigned int	arg_pos;
	int				arg;

	arg_pos = new_idx(cursor->pc, 3, FALSE);
	enc = vm->arena[new_idx(cursor->pc, 1, 0)];
	type = get_arg_type(enc, 2);
	if (type == REG)
	{
		arg = convert_to_int(vm->arena, arg_pos, 1);
		if (0 < arg && arg <= 16)
			*value = cursor->reg[arg];
		else
			return (ERROR);
	}
	else
	{
		arg = convert_to_int(vm->arena, arg_pos, 2);
		if (type == DIR)
			*value = arg;
		else
			*value = convert_to_int(vm->arena, new_idx(cursor->pc, 3, 0), 2);
	}
	return (SUCCESS);
}

static int	get_arg_3_value(t_vm *vm, t_cursor *cursor, int *value)
{
	int				type;
	unsigned char	enc;
	unsigned int	arg_pos;
	unsigned int	arg;

	enc = vm->arena[new_idx(cursor->pc, 1, 0)];
	if (get_arg_type(enc, 2) == REG)
		arg_pos = new_idx(cursor->pc, 4, FALSE);
	else
		arg_pos = new_idx(cursor->pc, 5, FALSE);
	type = get_arg_type(enc, 3);
	if (type == REG)
	{
		arg = convert_to_int(vm->arena, arg_pos, 1);
		if (0 < arg && arg <= 16)
			*value = cursor->reg[arg];
		else
			return (ERROR);
	}
	else if (type == DIR)
	{
		arg = convert_to_int(vm->arena, arg_pos, 2);
		*value = arg;
	}
	return (SUCCESS);
}

static int	op_sti_check(t_vm *vm, t_cursor *cursor)
{
	unsigned char	enc;

	enc = vm->arena[new_idx(cursor->pc, 1, 0)];
	if (get_arg_type(enc, 4) != 0 || \
		get_arg_type(enc, 3) == 0 || \
		get_arg_type(enc, 3) == IND || \
		get_arg_type(enc, 2) == 0 || \
		get_arg_type(enc, 1) != REG)
	{
		cursor->pc = new_idx(cursor->pc, 1, FALSE);
		return (ERROR);
	}
	return (SUCCESS);
}

static void	vis_sti(t_vm *vm, t_cursor *cursor, unsigned int store_idx)
{
	int	bold;
	int	inverse;
	int	bytes;

	bold = TRUE;
	inverse = FALSE;
	bytes = 4;
	if (vm->vis == NULL)
		return ;
	vm->vis->attr[cursor->player](vis_calc_att(bold, inverse), vm->vis->graphics->arena);
	vm->vis->index = store_idx;
	vm->vis->bytes = bytes;
	vis_print_cursor(vm->vis);
}

void	op_sti(t_vm *vm, t_cursor *cursor)
{
	int				arg_1;
	int				arg_2_value;
	int				arg_3_value;
	unsigned int	store_idx;

	if (op_sti_check(vm, cursor) != SUCCESS)
		return ;
	arg_1 = convert_to_int(vm->arena, new_idx(cursor->pc, 2, 0), 1);
	if (arg_1 <= 0 || arg_1 > 16 || \
		get_arg_2_value(vm, cursor, &arg_2_value) == ERROR || \
		get_arg_3_value(vm, cursor, &arg_3_value) == ERROR)
	{
		cursor->pc = new_idx(cursor->pc, 1, FALSE);
		return ;
	}
	store_idx = new_idx(cursor->pc, arg_2_value + arg_3_value, FALSE);
	store_in_arena(vm->arena, store_idx, 4, cursor->reg[arg_1]);
	vis_sti(vm, cursor, store_idx);
}
