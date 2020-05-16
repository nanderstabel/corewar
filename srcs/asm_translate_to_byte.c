/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_translate_to_byte.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/16 17:58:23 by zitzak        ########   odam.nl         */
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

void			write_byte_to_buf(t_project *as, unsigned char byte)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	as->buffer[as->index] = byte;
	as->index++;
	if (as->index == CHAMP_MAX_SIZE + 1)
		add_buffer_to_list(as);
}

void			write_str_to_buf(t_project *as, char *to_bytecode, unsigned char type)
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
	while (index < (int)type)
	{
		write_byte_to_buf(as, (unsigned char)str[index]);
		index++;
	}
	//Moeten nog free()
}

t_bool			translate_indirect_label(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	
	return (SUCCESS);
}

t_bool			translate_instruction(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	return (SUCCESS);
	as->opcode_temp = 0;
	write_byte_to_buf(as, as->current_token->opcode);
	if (as->current_token->encoding)
	{
		as->opcode_temp = as->current_token->opcode;
		write_byte_to_buf(as, as->current_token->encoding);
	}
	return (SUCCESS);
}

t_bool			translate_register(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	return (SUCCESS);
	write_str_to_buf(as, as->current_token->literal_str + 1, (unsigned char)token_tab[REGISTER].size);
	
	
	return (SUCCESS);
}

t_bool			translate_direct_label(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	
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
	
	return (SUCCESS);
}

/*
** -------------------------------------------------------------------------- **
** translation_check checks whether the token type of the current token has a
** translate function stored in in the token table, if so, it calls that
** translate function and returnes whatever it returns. If there is no
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
	as->buffer = (char*)ft_memalloc(sizeof(CHAMP_MAX_SIZE + 1));
	if (!as->buffer)
		return (FAIL);
	return (loop_token_list(as, translation_check));
}
