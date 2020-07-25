/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_aff.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 16:46:55 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/23 17:08:59 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		op_aff(t_vm *vm, t_cursor *cursor)
{
	unsigned char	enc;
	char			arg;
	char			arg_value;

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
	cursor->pc = new_idx(cursor->pc, 3, FALSE);
	return (SUCCESS);
}
