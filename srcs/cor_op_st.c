/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_st.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 16:51:19 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/29 11:30:47 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	op_st_check(t_vm *vm, t_cursor *cursor)
{
	unsigned char	enc;

	enc = vm->arena[new_idx(cursor->pc, 1, 0)];
	if (get_arg_type(enc, 4) != 0 || \
		get_arg_type(enc, 3) != 0 || \
		get_arg_type(enc, 2) == 0 || \
		get_arg_type(enc, 2) == DIR || \
		get_arg_type(enc, 1) == 0 ||
		get_arg_type(enc, 1) != REG)
		return (ERROR);
	if (vm->a_option)
		vm->a_string = ft_catprintf(vm->a_string, FORMAT_A, cursor->p, \
			g_op_tab[cursor->op_code - 1].operation);
	return (SUCCESS);
}

static void	vis_st(t_vm *vm, t_cursor *cursor, int offset)
{
	int	bold;
	int	inverse;
	int	bytes;

	bold = TRUE;
	inverse = FALSE;
	bytes = 4;
	if (vm->vis == NULL)
		return ;
	vm->vis->attr[cursor->player](vis_calc_att(bold, inverse), \
		vm->vis->graphics->arena);
	vm->vis->index = new_idx(cursor->pc, offset, FALSE);
	vm->vis->bytes = bytes;
	vis_print_cursor(vm->vis);
}

int			op_st(t_vm *vm, t_cursor *cursor)
{
	int		params[4];

	if (op_st_check(vm, cursor) != SUCCESS)
		return (ERROR);
	params[0] = 2;
	params[1] = REG;
	params[2] = 0;
	params[3] = 0;
	if (get_value(vm, cursor, params) == SUCCESS)
	{
		if (get_arg_type(vm->arena[new_idx(cursor->pc, 1, FALSE)], 2) == REG)
		{
			params[2] = \
				convert_to_int(vm->arena, new_idx(cursor->pc, params[0], 0), 1);
			if (!(params[2] > 0 && params[2] <= REG_NUMBER))
				return (ERROR);
			cursor->reg[params[2]] = params[1];
			if (vm->a_option)
				ft_putstr(ft_catprintf(vm->a_string, " %i\n", params[2]));
		}
		else
		{
			params[2] = \
				convert_to_int(vm->arena, new_idx(cursor->pc, params[0], 0), 2);
			store_in_arena(vm->arena, \
				new_idx(cursor->pc, params[2], 0), 4, params[1]);
			vis_st(vm, cursor, params[2]);
			if (vm->a_option)
				ft_putstr(ft_catprintf(vm->a_string, " %i\n", params[2]));
		}
	}
	return (SUCCESS);
}
