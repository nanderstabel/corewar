/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_live.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 11:20:48 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/08/08 12:03:38 by lhageman      ########   odam.nl         */
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
	usleep(10000);
	vm->vis->attr[cursor->player](vis_calc_att(FALSE, FALSE), \
		vm->vis->graphics->arena);
	vm->vis->index = cursor->pc;
	vm->vis->bytes = bytes;
	vis_print_cursor(vm->vis);
}

void		op_live(t_vm *vm, t_cursor *cursor)
{
	int				arg;

	if (vm->a_option)
		vm->a_string = ft_catprintf(vm->a_string, FORMAT_A, cursor->p, \
			g_op_tab[cursor->op_code - 1].operation);
	arg = convert_to_int(vm->arena, new_idx(cursor->pc, 1, FALSE), 4);
	if (0 < -arg && -arg <= (int)vm->champ_count)
	{
		vm->last_live = -arg;
		if (vm->f_option)
			ft_printf(FORMAT_F, -arg, vm->champ[-arg]->header.prog_name);
	}
	cursor->decay = 0;
	++(vm->live_count);
	vis_live(vm, cursor);
	if (vm->a_option)
		ft_putstr(ft_catprintf(vm->a_string, " %i\n", arg));
}
