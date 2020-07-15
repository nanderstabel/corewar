/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_st.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 16:51:19 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/13 17:05:13 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// If Argument2 is of type T_REG, set value from registry <Argument1> into registry <Argument2>
// If Argument2 is of type T_IND, set value from registry <Argument1> into memory. 
// Address is calculated as follows: (current_position + (Argument2 % IDX_MOD))

// REG 01	1	Registry Rx (where х = registry number, 1 to REG_NUMBER)			
// DIR 10	2-4	A number, saved on 2 or 4 bytes, depending on label			
// IND 11	2	Relative address, read 4 bytes from position <±T_IND bytes>

// 01010000
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
	{
		return (ERROR);
	}
	else
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
	vm->vis->attr[cursor->player](vis_calc_att(bold, inverse), vm->vis->graphics->arena);
	vm->vis->index = new_idx(cursor->pc, offset, FALSE);
	vm->vis->bytes = bytes;
	vis_print_cursor(vm->vis);
}

void		op_st(t_vm *vm, t_cursor *cursor)
{
	int		arg_1;
	int		arg_2;
	int		type;

	type = get_arg_type(vm->arena[new_idx(cursor->pc, 1, FALSE)], 2);
	arg_1 = convert_to_int(vm->arena, new_idx(cursor->pc, 2, 0), 1);
	if (op_st_check(vm, cursor) != SUCCESS || arg_1 <= 0 || 16 < arg_1)
	{
		cursor->pc = new_idx(cursor->pc, 1, FALSE);
		return ;
	}
	if (type == REG)
	{
		arg_2 = convert_to_int(vm->arena, new_idx(cursor->pc, 3, 0), 1);
		if (0 < arg_2 && arg_2 <= REG_NUMBER)
		{
			cursor->reg[arg_2] = cursor->reg[arg_1];
			cursor->pc = new_idx(cursor->pc, 4, FALSE);
		}
		else
			cursor->pc = new_idx(cursor->pc, 1, FALSE);
	}
	else if (type == IND)
	{
		arg_2 = convert_to_int(vm->arena, new_idx(cursor->pc, 3, 0), 2);
		store_in_arena(vm->arena, new_idx(cursor->pc, arg_2, FALSE), 4, \
			cursor->reg[arg_1]);
		vis_st(vm, cursor, arg_2);
		cursor->pc = new_idx(cursor->pc, 5, FALSE);
	}
}
