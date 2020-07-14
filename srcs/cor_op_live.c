/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_live.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 11:20:48 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/13 13:24:41 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

//TODO: double check whether an invalid argument for live (when the id doesn't match a player) does.

static void	vis_live(t_vm *vm, t_cursor *cursor)
{
	int	bold;
	int	inverse;
	int	bytes;

	bold = FALSE;
	inverse = TRUE;
	bytes = 1;
	if (vm->vis == NULL)
		return ;
	vm->vis->attr[cursor->player](vis_calc_att(bold, inverse), vm->vis->graphics->arena);
	vm->vis->index = cursor->pc;
	vm->vis->bytes = bytes;
	vis_print_cursor(vm->vis);
	vm->vis->attr[cursor->player](vis_calc_att(bold, FALSE), vm->vis->graphics->arena);
	vm->vis->index = cursor->pc;
	vm->vis->bytes = bytes;
	vis_print_cursor(vm->vis);
}

void	op_live(t_vm *vm, t_cursor *cursor)
{
	int				arg;

	arg = convert_to_int(vm->arena, new_idx(cursor->pc, 1, FALSE), 4);
	if (arg == cursor->reg[1])
	{
		vm->last_live = arg;
		++(vm->live_count);
		cursor->decay = 0;
		if (vm->vis == NULL)
			ft_printf("A process shows that player %d (%s) is alive\n", \
				arg, vm->champ[arg]->header.prog_name);
		vis_live(vm, cursor);
		cursor->pc = new_idx(cursor->pc, 5, FALSE);
		// If wanted live count for champ
		return ;
	}
	else
		cursor->pc = new_idx(cursor->pc, 1, FALSE);
	return ;
}
