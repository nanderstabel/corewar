/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_vm_start.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 11:22:16 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/21 14:59:52 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_cursors(t_vm *vm)
{
	t_cursor	*current;
	int			idx;

	current = vm->cursors;
	idx = vm->champ_count;
	while (current && idx > 0)
	{
		vm->vis->attr[current->player](vis_calc_att(0, 0), \
			vm->vis->graphics->arena);
		vm->vis->index = current->pc;
		vm->vis->bytes = vm->champ[idx]->header.prog_size;
		vis_print_cursor(vm->vis);
		current = current->next;
		--idx;
	}
}

int	cursors_init(t_vm *vm)
{
	unsigned int	idx;
	t_cursor		*new_cursor;

	idx = 1;
	ft_printf("Introducing contestants...\n");
	while (idx <= vm->champ_count)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", idx, \
		vm->champ[idx]->header.prog_size, vm->champ[idx]->header.prog_name, \
		vm->champ[idx]->header.comment);
		new_cursor = (t_cursor*)ft_memalloc(sizeof(t_cursor));
		if (new_cursor == NULL)
			return (ERROR);
		new_cursor->pc = (MEM_SIZE / vm->champ_count) * (idx - 1);
		ft_memcpy(&(vm->arena[new_cursor->pc]), vm->champ[idx]->exec_code, \
			vm->champ[idx]->header.prog_size);
		new_cursor->reg[1] = -idx;
		new_cursor->next = vm->cursors;
		vm->cursors = new_cursor;
		new_cursor->player = idx;
		// ft_printf("with exec_code:\n");
		// put_exec_code(vm->champ[idx]->exec_code, vm->champ[idx]->header.prog_size);
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
	if (cursors_init(vm) == ERROR)
		return (ERROR);
	if (vm->visualizer == TRUE)
	{
		vm->vis = ft_memalloc(sizeof(t_vis));
		if (vm->vis == NULL)
			return (ERROR);
		vis_create(vm);
		print_cursors(vm);
	}
	while (vm->cursors != NULL && (vm->dump == -1 ||\
		(vm->dump > 0 && (unsigned int)(vm->dump) > vm->total_cycle_count)))
		game_loop(vm, operations);
	vis_exit(vm);
	return (SUCCESS);
}
