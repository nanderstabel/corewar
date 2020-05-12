/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_main.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:02:07 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/12 13:41:04 by nstabel       ########   odam.nl         */
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
	END
}	e_state;

static t_state	g_transitions[][2] =
{
	[INITIALIZE] = {END, SET_OPTIONS},
	[SET_OPTIONS] = {END, GET_INPUT_FILE},
	[GET_INPUT_FILE] = {END, ANALYZE_LEXICON},
	[ANALYZE_LEXICON] = {END, TOKENIZE_INPUT},
	[TOKENIZE_INPUT] = {END, ANALYZE_SYNTAX},
	[ANALYZE_SYNTAX] = {END, ANALYZE_PARAMETERS},
	[ANALYZE_PARAMETERS] = {END, ANALYZE_INSTRUCTIONS},
	[ANALYZE_INSTRUCTIONS] = {END, CREATE_OUTPUT_FILE},
	[CREATE_OUTPUT_FILE] = {END, TRANSLATE_TO_BYTE},
	[TRANSLATE_TO_BYTE] = {END, WRITE_TRANSLATION},
	[WRITE_TRANSLATION] = {END, END}
};

static t_event	g_events[] =
{
	[SET_OPTIONS] = set_options,
	[GET_INPUT_FILE] = get_input_file,
	[ANALYZE_LEXICON] = analyze_lexicon,
	[TOKENIZE_INPUT] = tokenize_input,
	[ANALYZE_SYNTAX] = analyze_syntax,
	[ANALYZE_PARAMETERS] = analyze_parameters,
	[ANALYZE_INSTRUCTIONS] = analyze_instructions,
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
	if (install_machine(&machine, END))
		run_machine(machine, as, g_transitions, g_events);
	uninstall_machine(&machine);
	return (0);
}
