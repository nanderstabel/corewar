/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_fork.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 16:47:25 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/24 12:01:07 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		op_fork(t_vm *vm, t_cursor *cursor)
{
	int			arg;
	t_cursor	*new_cursor;

	arg = convert_to_int(vm->arena, new_idx(cursor->pc, 1, FALSE), 2);
	new_cursor = (t_cursor *)malloc(sizeof(t_cursor));
	ft_memmove(new_cursor, cursor, sizeof(t_cursor));
	new_cursor->pc = new_idx(cursor->pc, arg, FALSE);
	new_cursor->next = vm->cursors;
	vm->cursors = new_cursor;
	cursor->pc = new_idx(cursor->pc, 3, FALSE);
	return (SUCCESS);
}
