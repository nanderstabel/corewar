/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_translate_to_byte.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/22 16:46:15 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			add_buffer_to_list(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	ft_lstadd_back(&as->bytecode_list, ft_lstnew_ptr((void*)as->buffer,
	CHAMP_MAX_SIZE + 1));
	as->index = 0;
	as->buffer = (char*)ft_memalloc(CHAMP_MAX_SIZE + 1);
}

void			write_byte_to_buf(t_project *as, char byte)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	as->buffer[as->index] = byte;
	as->index++;
	if (as->index == CHAMP_MAX_SIZE + 1)
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

t_bool			translate_label(t_project *as)
{
	t_elem		*hash_element;
	char		*string;
	int			sum;

	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	string = label_to_key(as->current_token->literal_str,
	as->current_token->token_type);
	hash_element = ft_hash_table_get(as->labels, string);
	free(string);
	if (!hash_element)
		return (FAIL);
	if (as->pc > (size_t)hash_element->content)
		sum = ((long long)hash_element->content - (long long)as->pc);
	else
		sum = (long long)as->pc + (long long)hash_element->content;
	string = ft_itoa(sum);
	write_str_to_buf(as, string,
	(unsigned char)token_tab[as->current_token->token_type].size);
	free(string);
	return (SUCCESS);
}

t_bool			translate_instruction(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	as->opcode_temp = 0;
	as->pc = 0;
	write_byte_to_buf(as, as->current_token->opcode);
	if (as->current_token->encoding)
	{
		as->opcode_temp = as->current_token->opcode;
		write_byte_to_buf(as, as->current_token->encoding);
	}
	as->pc = as->current_token->address;
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
		if (op_tab[as->opcode_temp - 1].label)
			size = 2;
		else
			size = 4;
	}
	else
		size = token_tab[as->current_token->token_type].size;
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
	if (token_tab[as->current_token->token_type].translate)
		return (token_tab[as->current_token->token_type].translate(as));
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
	as->buffer = (char*)ft_memalloc(CHAMP_MAX_SIZE + 1);
	if (!as->buffer)
		return (FAIL);
	return (loop_token_list(as, translation_check));
}
