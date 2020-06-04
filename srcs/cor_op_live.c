/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_live.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 11:20:48 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/06/02 11:20:48 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		op_live(t_vm *vm, t_cursor *cursor)
{
	int				arg;

	arg = convert_to_int(vm->arena[new_idx(cursor->pc, 1, FALSE)], 4);
	if (0 < -arg && -arg <= MAX_PLAYERS && \
		vm->champions[-arg] != NULL)
	{
		vm->last_live = arg;
		ft_printf("A process shows that player %d (%s) is alive\n", \
			-arg, vm->champions[-arg]->prog_name);
	}
	//call visualizer
	return (5);
}
