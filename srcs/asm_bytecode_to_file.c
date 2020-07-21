/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_bytecode_to_file.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 19:54:39 by nstabel       #+#    #+#                 */
/*   Updated: 2020/07/21 11:15:01 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool			byte_num_to_file(t_project *as, int num)
{
	long long	*ptr;
	char		*str;

	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	ptr = (long long*)ft_memalloc(sizeof(long long));
	*ptr = (long long)num;
	str = ft_strnew(4);
	ft_memcpy((void*)str, (const void*)ptr, 4);
	str = ft_memrev(str, 4);
	write(as->fd, str, 4);
	free(ptr);
	free(str);
	return (SUCCESS);
}

t_bool			check_str_to_long(int type, size_t max_size,
				size_t len)
{
	if (len > max_size)
	{
		if (type == COMMAND_NAME)
			ft_dprintf(2, "Champion name too long (Max length 128)\n");
		else
			ft_dprintf(2, "Champion comment too long (Max length 2048)\n");
		exit(0);
	}
	return (SUCCESS);
}

void			print_zero_bytes(t_project *as, size_t len, size_t max_size)
{
	while (len < max_size)
	{
		write(as->fd, "\0", 1);
		len++;
	}
}

t_bool			byte_string_to_file(t_project *as, int type, size_t max_size)
{
	size_t		len;

	as->tmp = as->token_list;
	while (as->tmp)
	{
		as->current_token = (t_token *)as->tmp->content;
		if (as->current_token->token_type == type)
		{
			as->current_token = (t_token *)as->tmp->next->content;
			len = ft_strlen(as->current_token->literal_str);
			if (!check_str_to_long(type, max_size, len))
				return (FAIL);
			write(as->fd, as->current_token->literal_str, len);
			print_zero_bytes(as, len, max_size);
			return (SUCCESS);
		}
		as->tmp = as->tmp->next;
	}
	return (SUCCESS);
}

t_bool			bytecode_to_file(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	byte_num_to_file(as, COREWAR_EXEC_MAGIC);
	byte_string_to_file(as, COMMAND_NAME, PROG_NAME_LENGTH);
	byte_num_to_file(as, 0);
	byte_num_to_file(as, (int)as->pc);
	byte_string_to_file(as, COMMAND_COMMENT, COMMENT_LENGTH);
	byte_num_to_file(as, 0);
	as->tmp = as->bytecode_list;
	while (as->tmp)
	{
		write(as->fd, as->tmp->content, as->tmp->content_size);
		as->tmp = as->tmp->next;
	}
	as->buffer = NULL;
	return (SUCCESS);
}
