/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_vm_game.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 17:44:34 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/27 13:46:12 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	get_size(t_cursor *cursor, int byte)
{
	if (byte == 0 || byte == 1)
		return (byte);
	else if (byte == 3)
		return (2);
	else
	{
		if (g_op_tab[cursor->op_code - 1].label)
			return (2);
		else
			return (4);
	}
}

static int	get_num_bytes(t_vm *vm, t_cursor *cursor)
{
	int		params[3];
	int		bytes;
	size_t	index;

	index = 0;
	bytes = (g_op_tab[cursor->op_code - 1].encoded) ? 2 : 1;
	if (g_op_tab[cursor->op_code - 1].encoded)
	{
		params[0] = get_arg_type(vm->arena[new_idx(cursor->pc, 1, FALSE)], 1);
		params[1] = get_arg_type(vm->arena[new_idx(cursor->pc, 1, FALSE)], 2);
		params[2] = get_arg_type(vm->arena[new_idx(cursor->pc, 1, FALSE)], 3);
	}
	else
		params[0] = DIR;
	while (index < g_op_tab[cursor->op_code - 1].n_args)
	{
		bytes += get_size(cursor, params[index]);
		index++;
	}
	return (bytes);
}

static void	put_adv(t_vm *vm, t_cursor *cursor, size_t size)
{
	unsigned int	idx;

	if (!vm->b_option)
		return ;
	idx = 0;
	if (cursor->op_code == 9 && cursor->carry)
		return ;
	ft_printf("ADV %i (0x%04x -> 0x%04x) ", \
		size, cursor->pc, cursor->pc + size);
	while (idx < size)
	{
		ft_printf("%s ", vis_itoa(vm->arena[cursor->pc + idx]));
		idx += 1;
	}
	ft_putchar('\n');
}

static void	play(t_vm *vm, t_cursor *cursor, t_op_table operations)
{
	size_t	size;

	if (cursor->ctw == 0)
	{
		cursor->op_code = convert_to_int(vm->arena, cursor->pc, 1);
		if (cursor->op_code > 0 && cursor->op_code <= 16)
			cursor->ctw = g_op_tab[cursor->op_code - 1].cycles_to_wait;
	}
	if (cursor->ctw > 0)
		--(cursor->ctw);
	++(cursor->decay);
	if (cursor->ctw == 0)
	{
		if (cursor->op_code > 0 && cursor->op_code <= 16)
		{
			size = get_num_bytes(vm, cursor);
			put_adv(vm, cursor, size);
			operations[cursor->op_code](vm, cursor);
			if (cursor->op_code != 9)
				cursor->pc = new_idx(cursor->pc, size, FALSE);
		}
		else
			cursor->pc = new_idx(cursor->pc, 1, FALSE);
	}
}

void		game_loop(t_vm *vm, t_op_table operations)
{
	t_cursor	*cursor;

	cursor = vm->cursors;
	++(vm->cycle_count);
	++(vm->total_cycle_count);
	if (vm->e_option)
		ft_printf("It is now cycle %i\n", vm->total_cycle_count);
	while (cursor != NULL)
	{
		play(vm, cursor, operations);
		cursor = cursor->next;
		if (vm->visualizer == TRUE)
			vis_print_data(vm);
	}
	if (vm->cycle_count == CYCLE_TO_DIE)
		perform_check(vm);
}
