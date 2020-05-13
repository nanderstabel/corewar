/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_analyze_instructions.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/11 16:07:54 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/13 03:18:19 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** -------------------------------------------------------------------------- **
** checks if the current token is of type INSTRUCTION. If this is the case,
** then it will loop through the op_tab table to check if the instruction
** is valid. If not, then an error message is printed and FAIL is returned.
** If the instruction is valid, then the opcode is saved as well as the
** information of the encoding byte (not the actual byte, just if one is needed
** later on in the translation to byte-code). In this case SUCCESS is returned.
** It also increments as->n_labels whenever it encounters a LABEL.
** params
**	as->current_token	the current token
**	op_tab				operation table
**	as->n_labels		number of labels (later used to malloc a hashtable)
** return
**	SUCCESS		in case no invalid INSTRUCTION is found
**	FAIL		in case the INSTRUCTION is invalid
*/

t_bool			instruction_check(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	if (as->current_token->token_type == INSTRUCTION)
	{
		as->index = 0;
		while (as->index < REG_NUMBER)
		{
			if (ft_strequ(op_tab[as->index].operation, \
				as->current_token->literal_str))
			{
				as->current_token->opcode = op_tab[as->index].opcode;
				as->current_token->encoding = op_tab[as->index].encoded;
				return (SUCCESS);
			}
			++as->index;
		}
		ft_printf(INSTRUCTION_ERR);
		ft_printf(ERROR_FORMAT, as->current_token->row, \
			as->current_token->column, \
			token_tab[as->current_token->token_type].string, \
			as->current_token->literal_str);
		return (FAIL);
	}
	else if (as->current_token->token_type == LABEL)
		++as->n_labels;
	return (SUCCESS);
}

/*
** -------------------------------------------------------------------------- **
** this is the main function for the instruction analysis. It gives
** instruction_check as an argument to loop_token_list and returns whatever
** loop_token_list returns.
** params
**	*as		project struct
** return
**	SUCCESS		in case the syntax instruction was successful
**	FAIL		in case the syntax instruction failed
*/

t_bool			analyze_instructions(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	return (loop_token_list(as, instruction_check));
}
