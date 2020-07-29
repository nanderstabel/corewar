/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_zjmp.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 16:52:34 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/29 11:20:13 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		op_zjmp(t_vm *vm, t_cursor *cursor)
{
	int		arg;

	if (vm->a_option)
		vm->a_string = ft_catprintf(vm->a_string, FORMAT_A, cursor->p, \
			g_op_tab[cursor->op_code - 1].operation);
	arg = convert_to_int(vm->arena, new_idx(cursor->pc, 1, FALSE), 2);
	if (cursor->carry)
	{
		cursor->pc = new_idx(cursor->pc, arg, FALSE);
		if (vm->a_option)
			vm->a_string = ft_catprintf(vm->a_string, " %i OK\n", arg);
	}
	else
	{
		cursor->pc = new_idx(cursor->pc, 3, FALSE);
		if (vm->a_option)
			vm->a_string = ft_catprintf(vm->a_string, " %i FAILED\n", arg);
	}
	return (SUCCESS);
}
