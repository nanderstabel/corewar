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
	unsigned int	arg_position;
	int				player_number;

	arg_position = new_idx(cursor->pc, 1, FALSE);
	vm->last_live = convert_to_int(arg_position, 4);
	player_number = -(vm->last_live);
	//call visualizer
	if (!(0 < player_number && player_number <= MAX_PLAYERS && \
		vm->champions[player_number != NULL]))
		return (ERROR);
	ft_printf("A process shows that player %d (%s) is alive\n", \
		player_number, vm->champions[player_number]->prog_name);
	return (SUCCESS);
}
