/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_get_argtype.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 20:25:50 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/15 22:46:38 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool			get_argtype(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
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
