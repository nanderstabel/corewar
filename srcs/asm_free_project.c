/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_free_project.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 20:44:21 by nstabel       #+#    #+#                 */
/*   Updated: 2020/07/09 19:56:17 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool			free_project(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	ft_free_hash_table(&as->labels, NULL);
	if (as->bytecode_list)
		ft_lstdel(&as->bytecode_list, ft_freezero);
	if (as->buffer)
		free(as->buffer);
	as->tmp = as->token_list->next;
	as->trail = as->token_list;
	del_token_list(as);
	if ((t_token *)as->token_list->content)
		free(((t_token *)as->token_list->content)->literal_str);
	free(as->token_list->content);
	free(as->token_list);
	free(as);
	return (SUCCESS);
}
