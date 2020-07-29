/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_vm_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 18:15:19 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/29 14:26:46 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	kill_cursor(t_vm *vm, t_cursor *cursor)
{
	t_cursor	*walk;

	if (vm->c_option)
		ft_printf("Process %i hasn't lived for %i cycles (CTD %i)\n", \
			cursor->p, cursor->decay, vm->ctd);
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
		if (tmp->decay >= vm->ctd)
			kill_cursor(vm, tmp);
	}
}

void		perform_check(t_vm *vm)
{
	++(vm->check_count);
	check_cursors(vm);
	if (vm->check_count == MAX_CHECKS || vm->live_count > NBR_LIVE)
	{
		vm->ctd -= CYCLE_DELTA;
		vm->check_count = 0;
		vm->live_count = 0;
	}
	vm->cycle_count = 0;
}
