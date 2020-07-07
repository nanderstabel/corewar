/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_write_translation.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/07/06 23:10:45 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool			write_magic(t_project *as)
{
	long long	*ptr;
	char		*str;
	
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	ptr = (long long*)ft_memalloc(sizeof(long long));
	*ptr = (long long)COREWAR_EXEC_MAGIC;
	str = ft_strnew(4);
	ft_memcpy((void*)str, (const void*)ptr, 4);
	str = ft_memrev(str, 4);
	write(as->fd, str, 4);
	return (SUCCESS);	
}

t_bool			write_name(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	as->tmp = as->token_list;
	while(as->tmp)
	{
		as->current_token = (t_token *)as->tmp->content;
		if (as->current_token->token_type == COMMAND_NAME)
		{
			as->current_token = (t_token *)as->tmp->next->content;
			ft_putendl(as->current_token->literal_str);
			ft_putendl("done");
		}
		as->tmp = as->tmp->next;
	}
	return (SUCCESS);	
}

t_bool			write_translation(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	write_magic(as);
	write_name(as);
	as->tmp = as->bytecode_list;
	while (as->tmp)
	{
		write(as->fd, as->tmp->content, as->tmp->content_size);
		as->tmp = as->tmp->next;
	}
	return (SUCCESS);	
}
