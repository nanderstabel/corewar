/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_loop_token_list.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 20:32:11 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/22 16:49:17 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool			del_token_node(t_project *as)
{
	t_list		*tmp_list;
	t_token		*tmp_token;

	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	tmp_list = as->tmp;
	as->tmp = as->trail;
	as->tmp->next = as->tmp->next->next;
	tmp_token = (t_token *)tmp_list->content;
	if (tmp_token->literal_str)
		free(tmp_token->literal_str);
	free(tmp_token);
	free(tmp_list);
	return (SUCCESS);
}

t_bool			del_token_list(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	while (as->tmp)
	{
		del_token_node(as);
		as->trail = as->tmp;
		as->tmp = as->tmp->next;
	}
	return (SUCCESS);
}

t_bool			loop_token_list(t_project *as, t_bool (*check)(t_project *as))
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t%s\n", __func__) : 0;
	as->tmp = as->token_list;
	if (!as->tmp)
		return (FAIL);
	while (as->tmp)
	{
		if (!as->tmp->next)
			break ;
		as->current_token = (t_token *)as->tmp->content;
		as->next_token = (t_token *)as->tmp->next->content;
		if (check(as) == FAIL)
		{
			if (!as->tmp->next)
				return (SUCCESS);
			return (FAIL);
		}
		as->trail = as->tmp;
		if (as->tmp)
			if (as->tmp->next)
				as->tmp = as->tmp->next;
	}
	return (SUCCESS);
}
