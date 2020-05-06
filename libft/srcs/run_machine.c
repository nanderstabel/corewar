/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_machine.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/18 14:07:13 by nstabel       #+#    #+#                 */
/*   Updated: 2020/04/12 14:34:32 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "machine.h"

/*
** For the program to be able to continue, it needs to update it's current
** state. To do this, it needs a transition value ('FAIL' or 'SUCCES') provided
** by an event. Both the current state and the transition value are used as
** indices in the transition table to find the new state of the machine.
*/

static void		update_current_state(t_machine *machine, t_state g_transitions[][2])
{
	machine->last_state = machine->current_state;
	machine->current_state = g_transitions[machine->last_state][machine->transition];
}

/*
** Depending on the current state, a corresponding event is executed. In this
** function the current state is used as an index for the array of function
** pointers ('machine->events'). Everytime an event occurs, it returns a
** transition ('FAIL' or 'SUCCES').
*/

static void		execute_event(t_machine *machine, t_project *project, t_event g_events[])
{
	machine->transition = g_events[machine->current_state](project);
}

/*
** Running the machine means that this function loops through the states and
** events until a breaking condition occurs. In each loop, first the current
** state gets updated, and then the corresponding event gets executed.
*/

void			run_machine(t_machine *machine, t_project *project, t_state g_transitions[][2], t_event g_events[])
{
	while (1)
	{
		update_current_state(machine, g_transitions);
		if (machine->current_state == machine->size)
			break ;
		execute_event(machine, project, g_events);
	}
}
