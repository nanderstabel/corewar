/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_helpers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/10 14:51:50 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/24 15:45:53 by nstabel       ########   odam.nl         */
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
	type = enc;
	if (no == 4)
		return (type);
	return (-1);
}

void	store_in_arena(unsigned char *arena, unsigned int idx, \
		unsigned int len, int value)
{
	unsigned int	i;

	i = len;
	while (i > 0)
	{
		arena[new_idx(idx, len - i, FALSE)] = ((unsigned char*)&value)[i - 1];
		--i;
	}
}

int		get_value(t_vm *vm, t_cursor *cursor, int param[4])
{
	int		i;

	i = 1;
	while (param[i])
	{
		if (param[i] == REG)
		{
			param[i] = convert_to_int(vm->arena, new_idx(cursor->pc, param[0], 0), 1);
			if (param[i] <= 0 || param[i] > REG_NUMBER)
				return (ERROR);
			param[i] = cursor->reg[param[i]];
			param[0] += 1;
		}
		else if (param[i] == IND)
		{
			param[i] = convert_to_int(vm->arena, new_idx(cursor->pc, param[0], 0), 2);
			param[i] = convert_to_int(vm->arena, new_idx(cursor->pc, param[i], 0), 4);
			param[0] += 2;
		}
		else if (param[i] == DIR)
		{
			param[i] = convert_to_int(vm->arena, new_idx(cursor->pc, param[0], 0), 2 * (1 + (g_op_tab[cursor->op_code - 1].label == 0)));
			param[0] += 2 * (1 + (g_op_tab[cursor->op_code - 1].label == 0));
		}
		++i;
	}
	return (SUCCESS);
}
