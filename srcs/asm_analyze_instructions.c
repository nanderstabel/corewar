/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_analyze_instructions.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/11 16:07:54 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/12 21:19:06 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool			instruction_check(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	if (as->current_token->token_type == INSTRUCTION)
	{
		as->index = 0;
		while (as->index < REG_NUMBER)
		{
			if (ft_strequ(op_tab[as->index].operation, as->current_token->literal_str))
				return (SUCCESS);
			++as->index;
		}
		ft_printf(INSTRUCTION_ERR ERROR_FORMAT, as->current_token->row, as->current_token->column, token_tab[as->current_token->token_type].string, as->current_token->literal_str);
		return (FAIL);
	}
	return (SUCCESS);
}

t_bool			analyze_instructions(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	return (loop_token_list(as, instruction_check));
}
