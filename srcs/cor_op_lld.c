/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_lld.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/13 14:08:58 by lhageman      #+#    #+#                 */
/*   Updated: 2020/07/27 13:49:49 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	op_lld_check(t_vm *vm, t_cursor *cursor)
{
	unsigned char	enc;

	enc = vm->arena[new_idx(cursor->pc, 1, 0)];
	if (get_arg_type(enc, 4) != 0 || \
		get_arg_type(enc, 3) != 0 || \
		get_arg_type(enc, 2) != REG || \
		get_arg_type(enc, 1) == 0 ||
		get_arg_type(enc, 1) == REG)
		return (ERROR);
	if (vm->a_option)
		ft_printf(FORMAT_A, cursor->p, g_op_tab[cursor->op_code - 1].operation);
	return (SUCCESS);
}

int			op_lld(t_vm *vm, t_cursor *cursor)
{
	int		params[4];

	if (op_lld_check(vm, cursor) != SUCCESS)
		return (ERROR);
	params[0] = 2;
	params[1] = get_arg_type(vm->arena[new_idx(cursor->pc, 1, TRUE)], 1);
	params[2] = 0;
	params[3] = 0;
	if (get_value(vm, cursor, params) == SUCCESS)
	{
		params[2] = \
			convert_to_int(vm->arena, new_idx(cursor->pc, params[0], 0), 1);
		if (params[2] > 0 && params[2] <= REG_NUMBER)
			cursor->reg[params[2]] = params[1];
		params[0]++;
		cursor->carry = (cursor->reg[params[2]]) ? 0 : 1;
		if (vm->a_option)
			ft_printf(" r%i\n", params[2]);
	}
	return (SUCCESS);
}
