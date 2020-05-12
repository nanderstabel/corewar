/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_analyze_syntax.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/12 13:55:40 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool			analyze_syntax(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;

	//op_tab;
	return (SUCCESS);	
}
