/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_translate_to_byte.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/15 13:28:08 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"




t_bool			translate_indirect_label(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	
	return (SUCCESS);
}

t_bool			translate_instruction(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	
	return (SUCCESS);
}

t_bool			translate_register(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	
	return (SUCCESS);
}

t_bool			translate_direct_label(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	
	return (SUCCESS);
}

t_bool			translate_direct(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	
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
	ft_hash_table_append(as->labels, label_columns);
	ft_puttbl(as->labels);
	return (loop_token_list(as, translation_check));
}
