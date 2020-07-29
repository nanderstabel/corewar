/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_zjmp.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 16:52:34 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/29 12:23:34 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		op_zjmp(t_vm *vm, t_cursor *cursor)
{
	int		arg;
	size_t	size;

	if (vm->a_option)
		vm->a_string = ft_catprintf(vm->a_string, FORMAT_A, cursor->p, \
			g_op_tab[cursor->op_code - 1].operation);
	arg = convert_to_int(vm->arena, new_idx(cursor->pc, 1, FALSE), 2);
	if (cursor->carry)
	{
		size = arg;
		if (vm->a_option)
			ft_putstr(ft_catprintf(vm->a_string, " %i OK\n", arg));
	}
	else
	{
		size = 3;
		if (vm->a_option)
			ft_putstr(ft_catprintf(vm->a_string, " %i FAILED\n", arg));
	}
	if (vm->b_option)
		put_adv(vm, cursor, size);
	cursor->pc = new_idx(cursor->pc, size, FALSE);
	return (SUCCESS);
}
