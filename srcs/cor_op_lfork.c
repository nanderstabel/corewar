/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_lfork.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/13 14:08:37 by lhageman      #+#    #+#                 */
/*   Updated: 2020/07/30 12:45:27 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		op_lfork(t_vm *vm, t_cursor *cursor)
{
	int			arg;
	t_cursor	*new_cursor;

	if (vm->a_option)
		vm->a_string = ft_catprintf(vm->a_string, FORMAT_A, cursor->p, \
			g_op_tab[cursor->op_code - 1].operation);
	arg = convert_to_int(vm->arena, new_idx(cursor->pc, 1, FALSE), 2);
	new_cursor = (t_cursor *)malloc(sizeof(t_cursor));
	ft_memmove(new_cursor, cursor, sizeof(t_cursor));
	new_cursor->pc = new_idx(cursor->pc, arg, TRUE);
	++vm->cursor_count;
	new_cursor->p = vm->cursor_count;
	new_cursor->decay = 0;
	new_cursor->next = vm->cursors;
	vm->cursors = new_cursor;
	if (vm->a_option)
		ft_putstr(ft_catprintf(vm->a_string, " %i (%i)\n", arg, cursor->pc + arg));
	return (SUCCESS);
}
