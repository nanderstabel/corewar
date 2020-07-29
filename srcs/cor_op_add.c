/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_add.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 16:45:01 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/29 11:26:20 by nstabel       ########   odam.nl         */
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
		return (ERROR);
	if (vm->a_option)
		vm->a_string = ft_catprintf(vm->a_string, FORMAT_A, cursor->p, \
			g_op_tab[cursor->op_code - 1].operation);
	return (SUCCESS);
}

int			op_add(t_vm *vm, t_cursor *cursor)
{
	int		params[4];

	if (op_add_check(vm, cursor) != SUCCESS)
		return (ERROR);
	params[0] = 2;
	params[1] = REG;
	params[2] = REG;
	params[3] = 0;
	if (get_value(vm, cursor, params) == SUCCESS)
	{
		params[3] = \
			convert_to_int(vm->arena, new_idx(cursor->pc, params[0], 0), 1);
		if (!(params[3] > 0 && params[3] <= REG_NUMBER))
			return (ERROR);
		cursor->reg[params[3]] = (params[1] + params[2]);
		cursor->carry = (cursor->reg[params[3]]) ? 0 : 1;
		if (vm->a_option)
			ft_putstr(ft_catprintf(vm->a_string, " r%i\n", params[3]));
	}
	return (SUCCESS);
}
