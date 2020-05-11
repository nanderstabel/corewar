/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 11:17:00 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/11 17:31:06 by zitzak        ########   odam.nl         */
/*   Updated: 2020/05/11 16:11:22 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"

# define OPTIONS				"agu"

enum
{
	DEBUG_O = (1 << 0),
	USAGE_O = (1 << 1)
}	e_flags;

typedef struct		s_project
{
	int				count;
	int				fd;
	int				argc;
	char			**argv;
	int				flags;
	size_t			index;
	char			*string;
	t_hash_table	*labels;
}					t_project;

t_bool				set_options(t_project *as);
t_bool				get_input_file(t_project *as);
t_bool				analyze_lexicon(t_project *as);
t_bool				tokenize_input(t_project *as);
t_bool				analyze_syntax(t_project *as);
t_bool				analyze_parameters(t_project *as);
t_bool				analyze_instructions(t_project *as);
t_bool				create_output_file(t_project *as);
t_bool				translate_to_byte(t_project *as);
t_bool				write_translation(t_project *as);
t_bool				lexical_analysis(t_machine *as);

#endif
