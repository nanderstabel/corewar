/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_print_usage_message.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 17:53:08 by nstabel       #+#    #+#                 */
/*   Updated: 2020/08/06 17:53:24 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool				print_usage_message(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t%s\n", __func__) : 0;
	ft_printf("Usage: ./asm [-%s] <sourcefile.s>\n", OPTIONS);
	ft_printf(\
	"\t-g : Debug mode: shows executed functions in chronological order\n");
	ft_printf("\t-u : Shows usage message\n");
	exit(0);
	return (SUCCESS);
}
