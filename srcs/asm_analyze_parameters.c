/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_analyze_parameters.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/15 02:28:28 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool			get_argtype(t_project *as)
{
	if (!as->next_token)
		return (FAIL);
	if (as->next_token->token_type == REGISTER)	
		as->octal = T_REG;
	else if (as->next_token->token_type == DIRECT_LABEL || \
		as->next_token->token_type == DIRECT)
		as->octal = T_DIR;
	else if (as->next_token->token_type == INDIRECT_LABEL || \
		as->next_token->token_type == INDIRECT)
		as->octal = T_IND;
	else
		return (FAIL);
	return (SUCCESS);
}

t_bool			loop_parameters(t_project *as)
{
	as->index = 0;
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
				if (as->next_token->token_type == DIRECT && \
					op_tab[as->current_token->opcode - 1].label)
					as->pc -= 2;
			}
		}
		else
			return (FAIL);
		++as->index;
	}
	if (((t_token *)as->tmp->next->content)->token_type != ENDLINE)
	{
		as->tmp = as->tmp->next;
		as->next_token = (t_token *)as->tmp->content;
		return (FAIL);
	}
	return (SUCCESS);
}

char			*label_to_key(char *str, char token)
{
	if (token == LABEL)
		return (ft_strndup(str, ft_nchar(str, LABEL_CHAR) - 1));
	if (token == INDIRECT_LABEL)
		return (ft_strsub(str, 1, ft_strlen(str) - 1));
	if (token == DIRECT_LABEL)
		return (ft_strsub(str, 2, ft_strlen(str) - 2));
	return (NULL);
}

t_bool			parameter_check(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	if (as->current_token->token_type == LABEL)
	{
		ft_hash_table_add(as->labels, label_to_key(as->current_token->literal_str, as->current_token->token_type), (void *)as->pc);
		as->tmp = as->trail;
		as->tmp->next = as->tmp->next->next;
	}
	else if (as->current_token->token_type == ENDLINE)
	{
		as->tmp = as->trail;
		//add del_token_node here
		as->tmp->next = as->tmp->next->next;
	}
	else if (as->current_token->token_type == INSTRUCTION)
	{
		as->current_token->address = as->pc;
		++as->pc;
		if (as->current_token->encoding)
			++as->pc;
		if (loop_parameters(as) == FAIL)
		{
			ft_printf("Invalid parameter %i type %s for instruction %s\n", as->index, token_tab[as->next_token->token_type].lower, as->current_token->literal_str);
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
	as->labels = ft_malloc_hash_table((as->n_labels * 2) + 1, "Labels", FORMAT_LEFT);
	return (loop_token_list(as, parameter_check));	
}
