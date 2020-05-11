/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_get_input_file.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/11 18:36:31 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** ---------------------------------------------------------------------------**
** Check if the argument given to ./asm has the right extension ('.s') and if 
** the file exists. If so, open the file into a file descriptor
**
** t_project *as		struct of type t_project. Holds all data for the asm
**
** return (SUCCESS)		if the argument given to ./asm is valid
** return (FAIL)		if the argument given to ./asm is invalid
*/

t_bool			get_input_file(t_project *as)
{
	char	*temp;

	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	temp = ft_strchr(*as->argv, '.');
	if ((temp == NULL) | (!ft_strequ(temp, ".s")))
	{
		ft_printf("string %s", *as->argv);
		print_usage_message(as);
		return (FAIL);
	}
	as->fd = open(*as->argv, O_RDONLY);
	if (as->fd == -1)
	{
		ft_printf("Can't read source file %s\n", *as->argv);
		return (FAIL);
	}
	return (SUCCESS);	
}
