/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_translate_to_byte.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/13 02:54:21 by nstabel       ########   odam.nl         */
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

t_bool			translation_check(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t%s\n", __func__) : 0;
	if (token_tab[as->current_token->token_type].translate)
		return (token_tab[as->current_token->token_type].translate(as));
	return (SUCCESS);
}

t_bool			translate_to_byte(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	return (loop_token_list(as, translation_check));
}
