/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_lfork.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/13 14:08:37 by lhageman      #+#    #+#                 */
/*   Updated: 2020/07/17 16:22:16 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		op_lfork(t_vm *vm, t_cursor *cursor)
{
	int			arg;
	t_cursor	*new_cursor;

	arg = convert_to_int(vm->arena, new_idx(cursor->pc, 1, FALSE), 2);
	new_cursor = (t_cursor *)malloc(sizeof(t_cursor));
	ft_memmove(new_cursor, cursor, sizeof(t_cursor));
	new_cursor->pc = arg;
	new_cursor->next = vm->cursors;
	vm->cursors = new_cursor;
	cursor->pc = new_idx(cursor->pc, arg, FALSE);
	return (SUCCESS);
}
