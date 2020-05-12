/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_analyze_parameters.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/12 21:19:19 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool			parameter_check(t_project *as)
{
	if (as->current_token->token_type == INSTRUCTION)
	{
		as->index = 0;
		while (as->index < REG_NUMBER)
		{
			if (!ft_strequ(op_tab[as->index].operation, as->current_token->literal_str))
				ft_printf(INSTRUCTION_ERR ERROR_FORMAT, as->next_token->row, as->next_token->column, token_tab[as->next_token->token_type].string, as->next_token->literal_str);
			else
				ft_printf("CORRECT\n");
			++as->index;
		}

	}
	return (SUCCESS);
}

t_bool			analyze_parameters(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	return (SUCCESS);
	return (loop_token_list(as, parameter_check));	
}
