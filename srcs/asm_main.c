/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_main.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:02:07 by nstabel       #+#    #+#                 */
/*   Updated: 2020/07/25 19:22:18 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_state	g_transitions[][2] =
{
	[INITIALIZE] = {FREE_PROJECT, SET_OPTIONS},
	[SET_OPTIONS] = {FREE_PROJECT, GET_INPUT_FILE},
	[GET_INPUT_FILE] = {FREE_PROJECT, ANALYZE_LEXICON},
	[ANALYZE_LEXICON] = {FREE_PROJECT, ANALYZE_SYNTAX},
	[ANALYZE_SYNTAX] = {FREE_PROJECT, ANALYZE_INSTRUCTIONS},
	[ANALYZE_INSTRUCTIONS] = {FREE_PROJECT, ANALYZE_PARAMETERS},
	[ANALYZE_PARAMETERS] = {FREE_PROJECT, TRANSLATE_TO_BYTE},
	[TRANSLATE_TO_BYTE] = {FREE_PROJECT, CREATE_OUTPUT_FILE},
	[CREATE_OUTPUT_FILE] = {FREE_PROJECT, BYTECODE_TO_FILE},
	[BYTECODE_TO_FILE] = {FREE_PROJECT, FREE_PROJECT},
	[FREE_PROJECT] = {UNINSTALL, UNINSTALL}
};

static t_event	g_events[] =
{
	[SET_OPTIONS] = set_options,
	[GET_INPUT_FILE] = get_input_file,
	[ANALYZE_LEXICON] = analyze_lexicon,
	[ANALYZE_SYNTAX] = analyze_syntax,
	[ANALYZE_INSTRUCTIONS] = analyze_instructions,
	[ANALYZE_PARAMETERS] = analyze_parameters,
	[TRANSLATE_TO_BYTE] = translate_to_byte,
	[CREATE_OUTPUT_FILE] = create_output_file,
	[BYTECODE_TO_FILE] = bytecode_to_file,
	[FREE_PROJECT] = free_project
};

static void			initialize_project(t_project **as)
{
	*as = (t_project *)ft_memalloc(sizeof(t_project));
}

int					main(int argc, char **argv)
{
	t_machine	*machine;
	t_project	*as;

	initialize_project(&as);
	as->argc = argc;
	as->argv = argv;
	if (install_machine(&machine, UNINSTALL))
		run_machine(machine, as, g_transitions, g_events);
	uninstall_machine(&machine);
	return (0);
}
