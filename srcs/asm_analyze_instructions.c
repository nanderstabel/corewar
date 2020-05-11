/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_analyze_instructions.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/11 16:07:54 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/11 16:08:22 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool			analyze_instructions(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	return (SUCCESS);	
}
