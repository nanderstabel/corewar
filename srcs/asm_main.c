/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_main.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:02:07 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/12 18:43:00 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

enum
{
	INITIALIZE,
	SET_OPTIONS,
	GET_INPUT_FILE,
	ANALYZE_LEXICON,
	TOKENIZE_INPUT,
	ANALYZE_SYNTAX,
	ANALYZE_PARAMETERS,
	ANALYZE_INSTRUCTIONS,
	CREATE_OUTPUT_FILE,
	TRANSLATE_TO_BYTE,
	WRITE_TRANSLATION,
	UNINSTALL
}	e_state;

static t_state	g_transitions[][2] =
{
	[INITIALIZE] = {UNINSTALL, SET_OPTIONS},
	[SET_OPTIONS] = {UNINSTALL, GET_INPUT_FILE},
	[GET_INPUT_FILE] = {UNINSTALL, ANALYZE_LEXICON},
	[ANALYZE_LEXICON] = {UNINSTALL, TOKENIZE_INPUT},
	[TOKENIZE_INPUT] = {UNINSTALL, ANALYZE_SYNTAX},
	[ANALYZE_SYNTAX] = {UNINSTALL, ANALYZE_INSTRUCTIONS},
	[ANALYZE_INSTRUCTIONS] = {UNINSTALL, ANALYZE_PARAMETERS},
	[ANALYZE_PARAMETERS] = {UNINSTALL, CREATE_OUTPUT_FILE},
	[CREATE_OUTPUT_FILE] = {UNINSTALL, TRANSLATE_TO_BYTE},
	[TRANSLATE_TO_BYTE] = {UNINSTALL, WRITE_TRANSLATION},
	[WRITE_TRANSLATION] = {UNINSTALL, UNINSTALL}
};

static t_event	g_events[] =
{
	[SET_OPTIONS] = set_options,
	[GET_INPUT_FILE] = get_input_file,
	[ANALYZE_LEXICON] = analyze_lexicon,
	[TOKENIZE_INPUT] = tokenize_input,
	[ANALYZE_SYNTAX] = analyze_syntax,
	[ANALYZE_INSTRUCTIONS] = analyze_instructions,
	[ANALYZE_PARAMETERS] = analyze_parameters,
	[CREATE_OUTPUT_FILE] = create_output_file,
	[TRANSLATE_TO_BYTE] = translate_to_byte,
	[WRITE_TRANSLATION] = write_translation
};

static void			initialize_project(t_project **as)
{
	*as = (t_project *)ft_memalloc(sizeof(t_project));
	(*as)->labels = ft_malloc_hash_table(101, "Labels", FORMAT_LEFT);
}

int					main(int argc, char **argv)
{
	t_machine	*machine;
	t_project	*as;//'asm' is a keyword in c so we can not use it as a variable
	
	initialize_project(&as);
	as->argc = argc;
	as->argv = argv;
	if (install_machine(&machine, UNINSTALL))
		run_machine(machine, as, g_transitions, g_events);
	uninstall_machine(&machine);
	return (0);
}
