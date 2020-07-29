/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_sti.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/13 15:10:22 by lhageman      #+#    #+#                 */
/*   Updated: 2020/07/28 12:01:27 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
		if (arg <= 0 || REG_NUMBER < arg)
			return (ERROR);
		*value = cursor->reg[arg];
		if (vm->a_option)
			ft_printf(" %i", *value);
	}
	else if (type == DIR || type == IND)
	{
		arg = convert_to_int(vm->arena, arg_pos, 2);
		if (type == DIR)
			*value = arg;
		else
			*value = convert_to_int(vm->arena, new_idx(cursor->pc, arg, 0), 4);
		if (vm->a_option)
			ft_printf(" %i", arg);
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
		if (arg <= 0 || REG_NUMBER < arg)
			return (ERROR);
		*value = cursor->reg[arg];
		if (vm->a_option)
			ft_printf(" %i\n", *value);
	}
	else if (type == DIR)
	{
		arg = convert_to_int(vm->arena, arg_pos, 2);
		*value = arg;
		if (vm->a_option)
			ft_printf(" %i\n", arg);
	}
	return (SUCCESS);
}

static int	op_sti_check(t_vm *vm, t_cursor *cursor)
{
	unsigned char	enc;

	enc = vm->arena[new_idx(cursor->pc, 1, 0)];
	if (get_arg_type(enc, 4) != 0 || \
		get_arg_type(enc, 3) == 0 || \
		get_arg_type(enc, 2) == 0 || \
		get_arg_type(enc, 3) == IND || \
		get_arg_type(enc, 1) != REG)
		return (ERROR);
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
	vm->vis->attr[cursor->player](vis_calc_att(bold, inverse), \
		vm->vis->graphics->arena);
	vm->vis->index = store_idx;
	vm->vis->bytes = bytes;
	vis_print_cursor(vm->vis);
}

int			op_sti(t_vm *vm, t_cursor *cursor)
{
	int				arg_1;
	int				arg_2_value;
	int				arg_3_value;
	unsigned int	store_idx;

	if (op_sti_check(vm, cursor) == ERROR)
		return (ERROR);
	if (vm->a_option)
		ft_printf(FORMAT_A, cursor->p, g_op_tab[cursor->op_code - 1].operation);
	arg_1 = convert_to_int(vm->arena, new_idx(cursor->pc, 2, 0), 1);
	if (vm->a_option)
		ft_printf(" r%i", arg_1);
	if (0 < arg_1 && arg_1 <= REG_NUMBER \
		&& get_arg_2_value(vm, cursor, &arg_2_value) == SUCCESS \
		&& get_arg_3_value(vm, cursor, &arg_3_value) == SUCCESS)
	{
		store_idx = new_idx(cursor->pc, arg_2_value + arg_3_value, FALSE);
		store_in_arena(vm->arena, store_idx, 4, cursor->reg[arg_1]);
		vis_sti(vm, cursor, store_idx);
		if (vm->a_option)
			ft_printf("%8c -> store to %i + %i = %i (with pc and mod %i)\n", \
				'|', arg_2_value, arg_3_value, arg_2_value + arg_3_value, \
				cursor->pc + ((arg_2_value + arg_3_value) % IDX_MOD));
	}
	return (SUCCESS);
}
