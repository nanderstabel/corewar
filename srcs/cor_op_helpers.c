/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_helpers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/10 14:51:50 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/10 16:31:31 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_arg_type(unsigned char enc, unsigned int no)
{
	char	type;

	type = (enc >> 6);
	if (no == 1)
		return (type);
	enc ^= (type << 6);
	type = (enc >> 4);
	if (no == 2)
		return (type);
	enc ^= (type << 4);
	type = (enc >> 2);
	if (no == 3)
		return (type);
	enc ^= (type << 2);
	type = (enc >> 2);
	if (no == 4)
		return (type);
	return (-1);
}

void	move_pc(t_vm *vm, t_cursor *cursor, unsigned int move)
{
	int		new_op_code;

	cursor->pc = new_idx(cursor->pc, move, FALSE);
	new_op_code = convert_to_int(&(vm->arena[cursor->pc]), 1);
	if (0 < new_op_code && new_op_code <= 16)
		cursor->ctw = g_op_tab[new_op_code - 1].cycles_to_wait;
}
