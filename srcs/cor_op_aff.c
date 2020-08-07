/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_aff.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 16:46:55 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/08/07 16:43:37 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_aff(t_vm *vm, t_cursor *cursor)
{
	unsigned char	enc;
	char			arg;
	unsigned char	arg_value;

	enc = convert_to_int(vm->arena, new_idx(cursor->pc, 1, FALSE), 1);
	if (get_arg_type(enc, 1) != REG || get_arg_type(enc, 2) != 0 || \
		get_arg_type(enc, 3) != 0 || get_arg_type(enc, 4) != 0)
		return ;
	arg = convert_to_int(vm->arena, new_idx(cursor->pc, 2, FALSE), 1);
	if (arg <= 0 || arg > REG_NUMBER)
		return ;
	arg_value = (unsigned char)(cursor->reg[(int)arg]);
	if (vm->vis != NULL)
		ft_putchar(arg_value);
}
