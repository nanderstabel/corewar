/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_vm_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 18:15:19 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/31 14:50:24 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	vis_reset_pc(t_vm *vm, t_cursor *cursor)
{
	if (vm->vis == NULL)
		return ;
	vm->vis->bytes = 1;
	vm->vis->index = cursor->pc;
	vm->vis->attr[cursor->player](vis_calc_att(FALSE, FALSE), \
		vm->vis->graphics->arena);
	vis_print_cursor(vm->vis);
}

static void	kill_cursor(t_vm *vm, t_cursor *cursor)
{
	t_cursor	*walk;

	if (vm->c_option)
		ft_printf("Process %i hasn't lived for %i cycles (CTD %i)\n", \
			cursor->p, cursor->decay, vm->ctd);
	vis_reset_pc(vm, cursor);
	if (vm->cursors != cursor)
	{
		walk = vm->cursors;
		while (walk != NULL)
		{
			if (walk->next == cursor)
				walk->next = cursor->next;
			walk = walk->next;
		}
	}
	else
		vm->cursors = cursor->next;
	ft_bzero(cursor, sizeof(t_cursor));
	free(cursor);
	cursor = NULL;
}

static void	check_cursors(t_vm *vm)
{
	t_cursor	*walk;
	t_cursor	*tmp;

	walk = vm->cursors;
	while (walk != NULL)
	{
		tmp = walk;
		walk = walk->next;
		if ((int)tmp->decay >= vm->ctd)
			kill_cursor(vm, tmp);
	}
}

void		perform_check(t_vm *vm)
{
	++(vm->check_count);
	check_cursors(vm);
	if (vm->check_count == MAX_CHECKS || vm->live_count >= NBR_LIVE \
		|| vm->ctd <= 0)
	{
		vm->ctd -= CYCLE_DELTA;
		if (vm->e_option)
			ft_printf("Cycle to die is now %i\n", vm->ctd, vm->live_count);
		vm->check_count = 0;
	}
	vm->live_count = 0;
	vm->cycle_count = 0;
}
