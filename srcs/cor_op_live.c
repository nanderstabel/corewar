/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_live.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 11:20:48 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/26 13:54:57 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

//TODO: double check whether an invalid argument for live (when the id doesn't match a player) does.

static void	vis_live(t_vm *vm, t_cursor *cursor)
{
	int	bold;
	int	inverse;
	int	bytes;

	bold = TRUE;
	inverse = TRUE;
	bytes = 1;
	if (vm->vis == NULL)
		return ;
	vm->vis->attr[cursor->player](vis_calc_att(bold, inverse), \
		vm->vis->graphics->arena);
	vm->vis->index = cursor->pc;
	vm->vis->bytes = bytes;
	vis_print_cursor(vm->vis);
	vis_print_data(vm);
	vm->vis->attr[cursor->player](vis_calc_att(FALSE, FALSE), \
		vm->vis->graphics->arena);
	vm->vis->index = cursor->pc;
	vm->vis->bytes = bytes;
	vis_print_cursor(vm->vis);
}

int			op_live(t_vm *vm, t_cursor *cursor)
{
	//ft_printf("pc: %i, live, cycle: %i\n", cursor->pc, vm->total_cycle_count);
	int				arg;

	arg = convert_to_int(vm->arena, new_idx(cursor->pc, 1, FALSE), 4);
	if (-arg == cursor->reg[1])
	{
		vm->last_live = arg;
		// if (vm->vis == NULL)
		// 	ft_printf("A process shows that player %d (%s) is alive\n", 
		// 		arg, vm->champ[arg]->header.prog_name);
	}
		++(vm->live_count);
		cursor->decay = 0;
		vis_live(vm, cursor);
	// If wanted live count for champ
	return (SUCCESS);
}
