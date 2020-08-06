/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_set_options.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/08/06 17:52:43 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool				read_argument(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t%s\n", __func__) : 0;
	if (as->argc > 1)
	{
		--as->argc;
		++as->argv;
		return (SUCCESS);
	}
	return (FAIL);
}

t_bool				find_dash(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t%s\n", __func__) : 0;
	if (**as->argv == '-')
	{
		++(*as->argv);
		return (SUCCESS);
	}
	while (as->argc > 1)
	{
		--as->argc;
		++as->argv;
	}
	return (FAIL);
}

t_bool				find_option(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t%s\n", __func__) : 0;
	if (ft_strchr(OPTIONS, **as->argv) && **as->argv)
	{
		if (**as->argv == 'u')
			return (FAIL);
		if (**as->argv == 'g')
			as->flags |= DEBUG_O;
		if (**as->argv == 'l')
			as->flags |= DEBUG_L;
		++(*as->argv);
		return (SUCCESS);
	}
	return (FAIL);
}

t_bool				validate_argument(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t%s\n", __func__) : 0;
	if (**as->argv == 0 && *(*as->argv - 1) != '-')
		return (SUCCESS);
	return (FAIL);
}

static t_state	g_transitions[][2] =
{
	[INITIALIZE_OPT] = {UNINSTALL_OPT, READ_ARGUMENT_OPT},
	[READ_ARGUMENT_OPT] = {UNINSTALL_OPT, FIND_DASH_OPT},
	[FIND_DASH_OPT] = {UNINSTALL_OPT, FIND_OPTION_OPT},
	[FIND_OPTION_OPT] = {VALIDATE_ARGUMENT_OPT, FIND_OPTION_OPT},
	[VALIDATE_ARGUMENT_OPT] = {PRINT_USAGE_MESSAGE_OPT, READ_ARGUMENT_OPT},
	[PRINT_USAGE_MESSAGE_OPT] = {UNINSTALL_OPT, UNINSTALL_OPT}
};

static t_event	g_events[] =
{
	[READ_ARGUMENT_OPT] = read_argument,
	[FIND_DASH_OPT] = find_dash,
	[FIND_OPTION_OPT] = find_option,
	[VALIDATE_ARGUMENT_OPT] = validate_argument,
	[PRINT_USAGE_MESSAGE_OPT] = print_usage_message
};

t_bool				set_options(t_project *as)
{
	t_machine	*machine;

	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	if (install_machine(&machine, UNINSTALL_OPT))
		run_machine(machine, as, g_transitions, g_events);
	uninstall_machine(&machine);
	return (SUCCESS);
}
