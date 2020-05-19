/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_translate_to_byte.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/19 22:10:21 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			add_buffer_to_list(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	ft_lstadd_back(&as->bytecode_list, ft_lstnew((void*)as->buffer, CHAMP_MAX_SIZE + 1)); //ft_lstadd_back(&as->bytecode_list, ft_lstnew((void*)as->buffer, sizeof(CHAMP_MAX_SIZE + 1)));  <-- deleted sizeof()
	as->index = 0;
	as->buffer = (char*)ft_memalloc(CHAMP_MAX_SIZE + 1); //(char*)ft_memalloc(sizeof(CHAMP_MAX_SIZE + 1)); <-- deleted sizeof()
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
		// ft_printf("index %d - string = %s byte = %c\n", index, to_bytecode, (unsigned char)str[index]);
		write_byte_to_buf(as, str[index]);
		index++;
	}
	//Moeten nog free()
}

t_bool			translate_indirect_label(t_project *as)
{
	t_elem	*hash_element;
	char	*number;
	int		sum;
	
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	hash_element = ft_hash_table_get(as->labels,label_to_key(
	as->current_token->literal_str, as->current_token->token_type));
	if (!hash_element)
		return (FAIL);
	if (as->pc > (size_t)hash_element->content)
		sum = ((long long)hash_element->content - (long long)as->pc);
	else
		sum = (long long)as->pc + (long long)hash_element->content;
	number = ft_itoa(sum);
	write_str_to_buf(as, number,
	(unsigned char)token_tab[INDIRECT_LABEL].size);
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

t_bool			translate_register(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	// ft_printf("lit str %s - size %d\n",  as->current_token->literal_str + 1, (unsigned char)token_tab[REGISTER].size);
	write_str_to_buf(as, as->current_token->literal_str + 1,
	token_tab[REGISTER].size);
	return (SUCCESS);
}

t_bool			translate_direct_label(t_project *as)
{
	t_elem	*hash_element;
	char	*number;
	int		sum;
	
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	hash_element = ft_hash_table_get(as->labels,label_to_key(
	as->current_token->literal_str, as->current_token->token_type));
	if (!hash_element)
		return (FAIL);
	if (as->pc > (size_t)hash_element->content)
		sum = ((long long)hash_element->content - (long long)as->pc);
	else
		sum = (long long)as->pc + (long long)hash_element->content;
	number = ft_itoa(sum);
	write_str_to_buf(as, number,
	token_tab[DIRECT_LABEL].size);
	return (SUCCESS);
}

t_bool			translate_direct(t_project *as)
{
	char		type;
	
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	if (op_tab[as->opcode_temp - 1].label)
		type = 2;
	else
		type = 4;
	write_str_to_buf(as, as->current_token->literal_str + 1, type);	
	return (SUCCESS);
}

t_bool			translate_indirect(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	write_str_to_buf(as, as->current_token->literal_str,
	token_tab[INDIRECT].size);
	return (SUCCESS);
}

/*
** -------------------------------------------------------------------------- **
** translation_check checks whether the token type of the current token has a
** translate function stored in in the token table, if so, it calls that
** translate function and returnes whatever it returnvoid			add_buffer_to_list(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	ft_lstadd_back(&as->bytecode_list, ft_lstnew((void*)as->buffer, CHAMP_MAX_SIZE + 1)); //ft_lstadd_back(&as->bytecode_list, ft_lstnew((void*)as->buffer, sizeof(CHAMP_MAX_SIZE + 1)));  <-- deleted sizeof()
	as->index = 0;
	as->buffer = (char*)ft_memalloc(CHAMP_MAX_SIZE + 1); //(char*)ft_memalloc(sizeof(CHAMP_MAX_SIZE + 1)); <-- deleted sizeof()
}
s. If there is no
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
	// ft_hash_table_append(as->labels, label_columns);//append column with addresses to the hashtable
	// ft_puttbl(as->labels);//prints the table (output may look weird)
	if (!as->buffer)
		return (FAIL);
	return (loop_token_list(as, translation_check));
}
