/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_create_output_file.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/07/21 11:40:32 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool			check_strings_to_long(t_project *as)
{
	t_list	*temp;

	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	temp = as->token_list;
	temp = temp->next;
	as->current_token = (t_token *)temp->content;
	if (ft_strlen(as->current_token->literal_str) > PROG_NAME_LENGTH)
	{
		ft_dprintf(2, "Champion name too long (Max length 128)\n");
		exit(0);
	}
	temp = temp->next->next;
	as->current_token = (t_token *)temp->content;
	if (ft_strlen(as->current_token->literal_str) > COMMENT_LENGTH)
	{
		ft_dprintf(2, "Champion comment too long (Max length 2048)\n");
		exit(0);
	}
	return (SUCCESS);
}

t_bool			get_extension(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	as->index = 0;
	as->count = 0;
	while (as->argv[0][as->index])
	{
		if (as->argv[0][as->index] == '.')
			as->count = as->index;
		++as->index;
	}
	return (SUCCESS);
}

t_bool			get_filename(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	get_extension(as);
	as->string = ft_strnew(as->index + 2);
	ft_strcpy(as->string, as->argv[0]);
	as->string[as->index - 1] = 'c';
	as->string[as->index] = 'o';
	as->string[as->index + 1] = 'r';
	ft_printf("Writing output program to %s\n", as->string);
	return (SUCCESS);
}

t_bool			open_file(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	close(as->fd);
	as->fd = open(as->string, O_WRONLY | O_CREAT, 0777);
	free(as->string);
	return (SUCCESS);
}

t_bool			create_output_file(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	if (!check_strings_to_long(as))
		return (FAIL);
	ft_lstadd_back(&as->bytecode_list, ft_lstnew_ptr((void*)as->buffer,
	as->index));
	get_filename(as);
	open_file(as);
	return (SUCCESS);
}
