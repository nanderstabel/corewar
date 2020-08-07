/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_helpers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/10 14:51:50 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/08/07 20:24:11 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			get_arg_type(unsigned char enc, unsigned int no)
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

void		store_in_arena(unsigned char *arena, unsigned int idx, \
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

static int	get_reg(t_vm *vm, t_cursor *cursor, int param[4], int i)
{
	param[i] = convert_to_int(vm->arena, new_idx(cursor->pc, param[0], 0), 1);
	if (param[i] <= 0 || param[i] > REG_NUMBER)
		return (ERROR);
	if (vm->a_option && !((6 <= cursor->op_code && cursor->op_code <= 8) \
		|| cursor->op_code == 10))
		vm->a_string = ft_catprintf(vm->a_string, "r%i", param[i]);
	param[i] = cursor->reg[param[i]];
	param[0] += 1;
	if (vm->a_option && ((6 <= cursor->op_code && cursor->op_code <= 8) \
		|| cursor->op_code == 10))
		vm->a_string = ft_catprintf(vm->a_string, "%i", param[i]);
	return (SUCCESS);
}

static void	get_dir_ind(t_vm *vm, t_cursor *cursor, int param[4], int i)
{
	if (param[i] == IND)
	{
		param[i] = convert_to_int(vm->arena, \
			new_idx(cursor->pc, param[0], 0), 2);
		if (cursor->op_code == 13)
			param[i] = convert_to_int(vm->arena, \
				new_idx(cursor->pc, param[i], 1), 2);
		else
			param[i] = convert_to_int(vm->arena, \
				new_idx(cursor->pc, param[i], 0), 4);
		if (vm->a_option)
			vm->a_string = ft_catprintf(vm->a_string, "%i", param[i]);
		param[0] += 2;
	}
	else if (param[i] == DIR)
	{
		param[i] = convert_to_int(vm->arena, new_idx(cursor->pc, param[0], 0), \
			2 * (1 + (g_op_tab[cursor->op_code - 1].label == 0)));
		if (vm->a_option)
			vm->a_string = ft_catprintf(vm->a_string, "%i", param[i]);
		param[0] += 2 * (1 + (g_op_tab[cursor->op_code - 1].label == 0));
	}
}

int			get_value(t_vm *vm, t_cursor *cursor, int param[4])
{
	int		i;

	i = 1;
	while (param[i])
	{
		if (vm->a_option)
			vm->a_string = ft_catprintf(vm->a_string, " ");
		if (param[i] == REG)
		{
			if (get_reg(vm, cursor, param, i) == ERROR)
				return (ERROR);
		}
		else if (param[i] != 0)
			get_dir_ind(vm, cursor, param, i);
		++i;
	}
	return (SUCCESS);
}
