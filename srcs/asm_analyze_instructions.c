/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_analyze_instructions.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/11 16:07:54 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/15 12:11:49 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** -------------------------------------------------------------------------- **
** this function tries to find the current INSTRUCTION. It loops through the
** operations stored in op_tab. If it finds the instruction, it's opcode gets
** updated, and the encoding variable is switched on (later used to calculate
** the encoding byte of the INSTRUCTION). SUCCESS is returned. If the
** INSTRUCTION is not found, FAIL is returned.
** params
**	as->current_token	the current token
**	op_tab				operation table
** return
**	SUCCESS				in case INSTRUCTION is found
**	FAIL				in case INSTRUCTION is not found
*/

t_bool			find_instruction(t_project *as)
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
	return (FAIL);
}

/*
** -------------------------------------------------------------------------- **
** if during the instruction analysis an invalid sequence is found, this
** function prints the corresponding error message. It prints the generic
** INSTRUCTION_ERR with ERROR_FORMAT.
** params
**	as->current_token	the current token
**	token_tab			table with valid sequences
** return
**	FAIL				in case the sequence is invalid
*/

t_bool			instruction_error(t_project *as)
{
	ft_printf(INSTRUCTION_ERR);
	ft_printf(ERROR_FORMAT, as->current_token->row + 1, \
		as->current_token->column + 1, \
		token_tab[as->current_token->token_type].string, \
		as->current_token->literal_str);
	return (FAIL);
}

/*
** -------------------------------------------------------------------------- **
** checks if the current token is of type INSTRUCTION. If this is the case,
** then it will check if find_instruction can find the INSTRUCTION. If it can,
** SUCCESS is returned, if not instruction_error is returned. If the current
** token type is a label, then n_labels is incremented (later used to initialize
** a label hashtable).
** params
**	as->current_token	the current token
**	as->n_labels		number of labels (later used to malloc a hashtable)
** return
**	SUCCESS					in case no invalid INSTRUCTION is found
**	instruction_error(as)	in case an error message is printed (== FAIL)
*/

t_bool			instruction_check(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	if (as->current_token->token_type == INSTRUCTION)
	{
		if (find_instruction(as) == SUCCESS)
			return (SUCCESS);
		return (instruction_error(as));
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
