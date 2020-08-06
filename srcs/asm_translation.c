/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_translation.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 18:04:26 by nstabel       #+#    #+#                 */
/*   Updated: 2020/08/06 18:04:44 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool			label_error(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	ft_dprintf(2, LABEL_ERR, as->string);
	ft_dprintf(2, ERROR_FORMAT, as->current_token->row + 1, \
	as->current_token->column + 1, \
	g_token_tab[as->current_token->token_type].string, \
	as->current_token->literal_str);
	free(as->string);
	exit(0);
	return (FAIL);
}

t_bool			translate_label(t_project *as)
{
	t_elem		*hash_element;
	int			sum;
	char		size;

	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	as->string = label_to_key(as->current_token->literal_str,
	as->current_token->token_type);
	hash_element = ft_hash_table_get(as->labels, as->string);
	if (!hash_element)
		return (label_error(as));
	free(as->string);
	sum = ((long long)hash_element->content - (long long)as->temp_addres);
	as->string = ft_itoa(sum);
	if (as->current_token->token_type == DIRECT_LABEL)
	{
		if (g_op_tab[as->opcode_temp - 1].label)
			size = 2;
		else
			size = 4;
	}
	else
		size = g_token_tab[as->current_token->token_type].size;
	write_str_to_buf(as, as->string, size);
	free(as->string);
	return (SUCCESS);
}

t_bool			translate_instruction(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	as->opcode_temp = as->current_token->opcode;
	as->temp_addres = 0;
	write_byte_to_buf(as, as->current_token->opcode);
	if (as->current_token->encoding)
	{
		write_byte_to_buf(as, as->current_token->encoding);
	}
	as->temp_addres = as->current_token->address;
	return (SUCCESS);
}
