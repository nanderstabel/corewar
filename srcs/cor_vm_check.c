/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_vm_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 18:15:19 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/10 16:52:58 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	kill_cursor(t_vm *vm, t_cursor *cursor)
{
	t_cursor	*walk;

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
	// play killing sound
}

static void	check_cursors(t_vm *vm)
{
	t_cursor *walk;
	t_cursor *del;

	walk = vm->cursors;
	while (walk->next != NULL)
	{
		if (walk->decay <= CYCLE_TO_DIE)
			walk = walk->next;
		else
		{
			if (vm->cursors == walk)
				vm->cursors = walk->next;
			del = walk;
			walk = walk->next;
			kill_cursor(vm, del);
		}
	}
	if (walk->decay <= CYCLE_TO_DIE)
		walk = walk->next;
	else
	{
		if (vm->cursors == walk)
			vm->cursors = NULL;
		kill_cursor(vm, walk);
	}
}

void		perform_check(t_vm *vm)
{
	++(vm->check_count);
	check_cursors(vm);
	if (vm->check_count == MAX_CHECKS)
	{
		vm->ctd -= CYCLE_DELTA;
		vm->check_count = 0;
	}
	vm->cycle_count = 0;
}

// if (live_count > NBR_LIVE)
// true: decrease CTD with CYCLE_DELTA
// false: if (check_count < MAX_CHECK)
// true: leave CTD as it is
// false: decrease CTDC with CYCLE_DELTA and set check_count to 0
// reset cycle_count
// check_count++
