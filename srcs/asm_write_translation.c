/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_write_translation.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/07/07 17:23:20 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool			write_number(t_project *as, int num)
{
	long long	*ptr;
	char		*str;
	
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	ptr = (long long*)ft_memalloc(sizeof(long long));
	*ptr = (long long)num;
	str = ft_strnew(4);
	ft_memcpy((void*)str, (const void*)ptr, 4);
	str = ft_memrev(str, 4);
	// ft_printf("str = %s\n", str);
	write(as->fd, str, 4);
	return (SUCCESS);	
}

// t_bool			write_header(t_project *as, int type, size_t max_size)
// {

// }

// t_bool			write_exec_code_size(t_project *as)
// {

// 	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
// 	as->pc
// 	return (SUCCESS);
// }



t_bool			write_name(t_project *as, int type, size_t max_size)
{
	size_t			len;
	int			*ptr;
	char		*str;
	// long long				test;

	// test = 0;

	ptr	= (int*)ft_memalloc(sizeof(int));
	*ptr = 0;
	str = ft_strnew(1);
	ft_memcpy((void*)str, (const void*)ptr, 1);

	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	as->tmp = as->token_list;
	while(as->tmp)
	{
		as->current_token = (t_token *)as->tmp->content;
		if (as->current_token->token_type == type)
		{
			as->current_token = (t_token *)as->tmp->next->content;
			len = ft_strlen(as->current_token->literal_str);
			if (len > max_size)
			{
				if (type == COMMAND_NAME)
					ft_dprintf(2, "Champion name too long (Max length 128)\n");
				else
					ft_dprintf(2, "Champion comment too long (Max length 2048)\n");
				return (FAIL);
			}
			write(as->fd, as->current_token->literal_str, len);
			ft_printf("len = %i -- max_size = %i\n", len, max_size);
			while (len < max_size)
			{
				// ft_printf("tst\n");
				write(as->fd, "\0", 1);
				len++;
			}
			return (SUCCESS);
		}
		as->tmp = as->tmp->next;
	}
	return (SUCCESS);	
}

t_bool			write_translation(t_project *as)
{
	// int			fill_bytes;

	// fill_bytes = 0;
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	write_number(as, COREWAR_EXEC_MAGIC);
	write_name(as, COMMAND_NAME, PROG_NAME_LENGTH);
	write_number(as, 0);

	// write(as->fd, (void*)fill_bytes, 4);
	ft_printf("pc = %u\n", as->pc);
	write_number(as, (int)as->pc);
	write_name(as, COMMAND_COMMENT, COMMENT_LENGTH);
	write_number(as, 0);

	as->tmp = as->bytecode_list;
	while (as->tmp)
	{
		write(as->fd, as->tmp->content, as->tmp->content_size);
		as->tmp = as->tmp->next;
	}
	return (SUCCESS);	
}
