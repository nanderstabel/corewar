/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_aff.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 16:46:55 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/27 13:50:24 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		op_aff(t_vm *vm, t_cursor *cursor)
{
	unsigned char	enc;
	char			arg;
	char			arg_value;

	// ft_printf(FORMAT_A, cursor->p, g_op_tab[cursor->op_code - 1].operation);
	enc = convert_to_int(vm->arena, new_idx(cursor->pc, 1, FALSE), 1);
	if (get_arg_type(enc, 1) != REG || get_arg_type(enc, 2) != 0 || \
		get_arg_type(enc, 3) != 0 || get_arg_type(enc, 4) != 0)
		return (ERROR);
	arg = convert_to_int(vm->arena, new_idx(cursor->pc, 2, FALSE), 1);
	if (0 < arg && arg <= REG_NUMBER)
	{
		arg_value = (char)(cursor->reg[(int)arg]);
		if (vm->vis != NULL)
			ft_putchar(arg_value);
	}
	// ft_printf(" %i\n", arg);//
	return (SUCCESS);
}
