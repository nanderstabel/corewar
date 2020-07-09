/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_analyze_parameters.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/07/09 17:21:51 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool			adjust_encoding_byte(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	if (as->current_token->encoding == 1)
		--as->current_token->encoding;
	as->current_token->encoding += token_tab[as->next_token->token_type].code;
	as->current_token->encoding = (as->current_token->encoding << 2);
	return (SUCCESS);
}


t_bool			count_parameters(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	while (as->index < op_tab[as->current_token->opcode - 1].n_args)
	{
		as->tmp = as->tmp->next;
		as->next_token = (t_token *)as->tmp->content;
		if (is_argument(as->next_token->token_type))
		{
			if (get_argtype(as))
			{
				if (!(op_tab[as->current_token->opcode - 1].args[as->index] & \
					as->octal))
					return (FAIL);
				as->pc += token_tab[as->next_token->token_type].size;
				if ((as->next_token->token_type == DIRECT || \
					as->next_token->token_type == DIRECT_LABEL) && \
					op_tab[as->current_token->opcode - 1].label)
					as->pc -= 2;
				if (as->current_token->encoding)
					adjust_encoding_byte(as);
			}
		}
		else
			return (FAIL);
		++as->index;
	}
	return (SUCCESS);
}

t_bool			loop_parameters(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	as->index = 0;
	if (count_parameters(as) == FAIL)
		return (FAIL);
	as->count = 0;
	while (as->current_token->encoding && as->index + as->count < 3)
	{
		as->current_token->encoding = (as->current_token->encoding << 2);
		++as->count;
	}
	if (((t_token *)as->tmp->next->content)->token_type != ENDLINE)
	{
		as->tmp = as->tmp->next;
		as->next_token = (t_token *)as->tmp->content;
		return (FAIL);
	}
	return (SUCCESS);
}

t_bool			parameter_check(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	if (as->current_token->token_type == LABEL)
	{
		as->string = label_to_key(as->current_token->literal_str, \
			as->current_token->token_type);
		if (!ft_hash_table_get(as->labels, as->string))
			ft_hash_table_add(as->labels, as->string, (void *)as->pc);
		del_token_node(as);
	}
	else if (as->current_token->token_type == ENDLINE)
		del_token_node(as);
	else if (as->current_token->token_type == INSTRUCTION)
	{
		as->current_token->address = as->pc;
		++as->pc;
		if (as->current_token->encoding)
			++as->pc;
		if (loop_parameters(as) == FAIL)
		{
			ft_dprintf(2, "Invalid parameter %i type %s for instruction %s\n", \
				as->index, token_tab[as->next_token->token_type].lower, \
				as->current_token->literal_str);
			return (FAIL);
		}
	}
	return (SUCCESS);
}

/*
** -------------------------------------------------------------------------- **
** this is the main function for the parameter analysis. It gives
** parameter_check as an argument to loop_token_list and returns whatever
** loop_token_list returns.
** params
**	*as		project struct
** return
**	SUCCESS		in case the parameter instruction was successful
**	FAIL		in case the parameter instruction failed
*/

t_bool			analyze_parameters(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	as->labels = ft_malloc_hash_table((as->n_labels * 2) + 1, NULL, NULL);
	return (loop_token_list(as, parameter_check));
}
