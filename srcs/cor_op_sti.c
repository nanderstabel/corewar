/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_sti.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/13 15:10:22 by lhageman      #+#    #+#                 */
/*   Updated: 2020/07/13 15:22:58 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
// "Value from the Argument1 is written to the memory, to the address: current_position + 
// ((Argument2 + Argument3) % IDX_MOD)
// If Argument2 is of type T_IND, value (4 bytes) for address calculation is read from 
// memory: current_position + (Argument2 % IDX_MOD)"							
// 11	sti	[T_REG]	[T_REG | T_DIR | T_IND]	[T_REG | T_DIR]	[00001011]	[0x0B]	store index ctw:25

static int	op_sti_check(t_vm *vm, t_cursor *cursor)
{
	unsigned char	enc;

	enc = vm->arena[new_idx(cursor->pc, 1, 0)];
	if (get_arg_type(enc, 4) != 0 || \
		get_arg_type(enc, 3) == 0 || \
		get_arg_type(enc, 3) == IND || \
		get_arg_type(enc, 2) == 0 || \
		get_arg_type(enc, 1) != REG)
	{
		cursor->pc = new_idx(cursor->pc, 1, FALSE);
		return (ERROR);
	}
	else
		return (SUCCESS);
}

void	op_sti(t_vm *vm, t_cursor *cursor)
{
	if (op_sti_check(vm, cursor) != SUCCESS)
		return ;
}
