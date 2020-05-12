/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_loop_token_list.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 20:32:11 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/12 20:59:26 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool			loop_token_list(t_project *as, t_bool (*check)(t_project *as))
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	as->tmp = as->token_list;
	if (!as->tmp)
		return (FAIL);
	while (as->tmp->next)
	{
		as->current_token = (t_token *)as->tmp->content;
		as->next_token = (t_token *)as->tmp->next->content;
		if (check(as) == FAIL)
			return (FAIL);
		as->tmp = as->tmp->next;
	}
	return (SUCCESS);
}
