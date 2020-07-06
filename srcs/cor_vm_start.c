/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_vm_start.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 11:22:16 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/06 12:57:28 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	cursors_init(t_vm *vm)
{
	unsigned int	idx;
	t_cursor		*new_cursor;

	idx = 1;
	ft_printf("Introducing contestants...\n");
	while (idx <= vm->champ_count)
	{
		ft_printf("Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", idx, \
		vm->champ[idx]->header.prog_size, vm->champ[idx]->header.prog_name, \
		vm->champ[idx]->header.comment);
		new_cursor = (t_cursor*)ft_memalloc(sizeof(t_cursor));
		if (new_cursor == NULL)
			return (ERROR);
		new_cursor->pc = (MEM_SIZE / vm->champ_count) * (idx - 1);
		ft_strcpy(&(vm->arena[new_cursor->pc]), vm->champ[idx]->exec_code);
		new_cursor->reg[0] = -idx;
		new_cursor->next = vm->cursors;
		vm->cursors = new_cursor;
		new_cursor->player = idx - 1;
		if (vm->vis)
		{
			vm->vis->attr[vm->vis->player](vis_calc_att(vm->vis->bold, \
			vm->vis->inverse), vm->vis->graphics->arena);
			vm->vis->index = new_cursor->pc;
			vm->vis->bytes = vm->champ[idx]->header.prog_size;
			vis_print_cursor(vm->vis);
		}
		++idx;
	}
	return (SUCCESS);
}

static void	set_op_table(t_op_table *operations)
{
	(*operations)[1] = op_live;
	(*operations)[2] = op_ld;
	(*operations)[3] = op_st;
	(*operations)[4] = op_add;
	(*operations)[5] = op_sub;
	(*operations)[6] = op_and;
	(*operations)[7] = op_or;
	(*operations)[8] = op_xor;
	(*operations)[9] = op_zjmp;
	(*operations)[10] = op_ldi;
	(*operations)[11] = op_sti;
	(*operations)[12] = op_fork;
	(*operations)[13] = op_lld;
	(*operations)[14] = op_lldi;
	(*operations)[15] = op_lfork;
	(*operations)[16] = op_aff;
}

int			vm_start(t_vm *vm)
{
	t_op_table	operations;

	set_op_table(&operations);
	vm->last_live = vm->champ[vm->champ_count]->id;
	vm->ctd = CYCLE_TO_DIE;
	if (vm->visualizer == TRUE)
	{
		vm->vis = ft_memalloc(sizeof(t_vis));
		if (vm->vis == NULL)
			return (ERROR);
		vis_create(vm);
	}
	if (cursors_init(vm) == ERROR)
		return (ERROR);
	// while (vm->cursors != NULL || vm->dump > vm->total_cycle_count)
	// 	game_loop(vm, operations);
	return (SUCCESS);
}
