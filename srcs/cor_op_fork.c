/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_fork.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 16:47:25 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/26 22:08:37 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		op_fork(t_vm *vm, t_cursor *cursor)
{
	int			arg;
	t_cursor	*new_cursor;

	ft_printf("P%5i | %s", cursor->p, g_op_tab[cursor->op_code - 1].operation);//
	arg = convert_to_int(vm->arena, new_idx(cursor->pc, 1, FALSE), 2);
	new_cursor = (t_cursor *)malloc(sizeof(t_cursor));
	ft_memmove(new_cursor, cursor, sizeof(t_cursor));
	new_cursor->pc = new_idx(cursor->pc, arg, FALSE);
	++vm->n_cursors;
	new_cursor->p = vm->n_cursors;
	new_cursor->next = vm->cursors;
	vm->cursors = new_cursor;
	ft_printf(" %i (%i)\n", arg, new_cursor->pc);//
	return (SUCCESS);
}
