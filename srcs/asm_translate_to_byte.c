/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_translate_to_byte.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/07/09 20:01:02 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			add_buffer_to_list(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	ft_lstadd_back(&as->bytecode_list, ft_lstnew_ptr((void*)as->buffer,
	CHAMP_MAX_SIZE));
	as->index = 0;
	as->buffer = (char*)ft_memalloc(CHAMP_MAX_SIZE);
}

void			write_byte_to_buf(t_project *as, char byte)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	as->buffer[as->index] = byte;
	as->index++;
	if (as->index == CHAMP_MAX_SIZE)
		add_buffer_to_list(as);
}

void			write_str_to_buf(t_project *as, char *to_bytecode, char type)
{
	long long	number;
	long long	*ptr;
	char		*str;
	int			index;

	index = 0;
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	number = ft_atoi(to_bytecode);
	ptr = (long long*)ft_memalloc(sizeof(long long));
	*ptr = number;
	str = ft_strnew(type);
	ft_memcpy((void*)str, (const void*)ptr, type);
	str = ft_memrev(str, type);
	while (index < type)
	{
		write_byte_to_buf(as, str[index]);
		index++;
	}
	free(str);
	free(ptr);
}

t_bool			label_error(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	ft_dprintf(2, LABEL_ERR, as->string);
	ft_dprintf(2, ERROR_FORMAT, as->current_token->row + 1, \
	as->current_token->column + 1, \
	g_token_tab[as->current_token->token_type].string, \
	as->current_token->literal_str);
	free(as->string);
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

t_bool			translate_argument(t_project *as)
{
	int		offset;
	char	size;

	offset = 0;
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	if (as->current_token->token_type == REGISTER ||
	as->current_token->token_type == DIRECT)
		offset = 1;
	if (as->current_token->token_type == DIRECT)
	{
		if (g_op_tab[as->opcode_temp - 1].label)
			size = 2;
		else
			size = 4;
	}
	else
		size = g_token_tab[as->current_token->token_type].size;
	write_str_to_buf(as, as->current_token->literal_str + offset, size);
	return (SUCCESS);
}

/*
** -------------------------------------------------------------------------- **
** translation_check checks whether the token type of the current token has a
** translate function stored in in the token table, if so, it calls that
** translate function and returnes whatever it return If there is no
** translate function stored, SUCCESS is returned.
** params
**	as->current_token	the current token
**	token_tab			token table
** return
**	.translate()		in case of available translate function
**	SUCCESS				if there is no need to translate
*/

t_bool			translation_check(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t%s\n", __func__) : 0;
	if (g_token_tab[as->current_token->token_type].translate)
		return (g_token_tab[as->current_token->token_type].translate(as));
	as->index = 0;
	return (SUCCESS);
}

/*
** -------------------------------------------------------------------------- **
** this is the main function for the translation to bytecode. It gives
** translation_check as an argument to loop_token_list and returns whatever
** loop_token_list returns.
** params
**	*as		project struct
** return
**	SUCCESS		in case the translation was successful
**	FAIL		in case the translation failed
*/

t_bool			translate_to_byte(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	as->index = 0;
	as->buffer = (char*)ft_memalloc(CHAMP_MAX_SIZE);
	if (!as->buffer)
		return (FAIL);
	return (loop_token_list(as, translation_check));
}
