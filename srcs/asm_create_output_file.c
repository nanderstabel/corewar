/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_create_output_file.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/07/06 22:39:29 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
	ft_putendl(as->string);
	return (SUCCESS);
}

t_bool			open_file(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	close(as->fd);
	as->fd = open(as->string, O_WRONLY | O_CREAT, 0777);//revise this
	return (SUCCESS);
}

t_bool			create_output_file(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	ft_lstadd_back(&as->bytecode_list, ft_lstnew_ptr((void*)as->buffer,
	as->index));
	get_filename(as);
	open_file(as);
	return (SUCCESS);	
}