/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_zjmp.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 16:52:34 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/27 10:43:45 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		op_zjmp(t_vm *vm, t_cursor *cursor)
{
	int		arg;

	if (vm->a_option)
		ft_printf("P%5i | %s", cursor->p, g_op_tab[cursor->op_code - 1].operation);//
	arg = convert_to_int(vm->arena, new_idx(cursor->pc, 1, FALSE), 2);
	if (cursor->carry)
	{
		cursor->pc = new_idx(cursor->pc, arg, FALSE);
		if (vm->a_option)
			ft_printf(" %i OK\n", arg);//
	}
	else
	{
		cursor->pc = new_idx(cursor->pc, 3, FALSE);
		if (vm->a_option)
			ft_printf(" %i FAILED\n", arg);//
	}
	return (SUCCESS);
}
