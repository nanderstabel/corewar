/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 11:17:00 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/06 20:27:45 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"

# define OPTIONS				"agu"

enum
{
	DEBUG_O = (1 << 0),
	USAGE_O = (1 << 1)
}	e_flags;

typedef struct		s_project
{
	int				count;
	int				argc;
	char			**argv;
	int				flags;
	size_t			index;
	char			*string;
}					t_project;

t_bool				set_options(t_project *as);
t_bool				get_input_file(t_project *as);
t_bool				tokenize_input(t_project *as);
t_bool				create_output_file(t_project *as);
t_bool				write_translation(t_project *as);

#endif
