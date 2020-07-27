/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_live.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 11:20:48 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/27 13:23:01 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
	int				arg;

	if (vm->a_option)
		ft_printf(FORMAT_A, cursor->p, g_op_tab[cursor->op_code - 1].operation);
	arg = convert_to_int(vm->arena, new_idx(cursor->pc, 1, FALSE), 4);
	if (arg == cursor->reg[1])
	{
		vm->last_live = arg;
		if (vm->f_option)
			ft_printf(FORMAT_F, -arg, vm->champ[-arg]->header.prog_name);
	}
	++(vm->live_count);
	cursor->decay = 0;
	vis_live(vm, cursor);
	if (vm->a_option)
		ft_printf(" %i\n", arg);
	return (SUCCESS);
}
