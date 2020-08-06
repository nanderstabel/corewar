/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_write_buffer.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 18:07:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/08/06 18:08:36 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			add_buffer_to_list(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	ft_lstadd_back(&as->bytecode_list, ft_lstnew_ptr((void*)as->buffer,
	CHAMP_MAX_SIZE));
	as->index = 0;
	as->buffer = (char*)ft_memalloc(CHAMP_MAX_SIZE);
}

void			write_byte_to_buf(t_project *as, char byte)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	as->buffer[as->index] = byte;
	as->index++;
	if (as->index == CHAMP_MAX_SIZE)
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
