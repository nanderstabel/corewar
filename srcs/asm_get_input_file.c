/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_get_input_file.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/11 17:26:31 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool			get_input_file(t_project *as)
{
	char	*temp;

	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	temp = ft_strchr(*as->argv, '.');
	if ((temp == NULL) | (!ft_strequ(temp, ".s")))
		ft_printf("ERROR");
	else
	{
		ft_printf("argc :%i\n argv %s\n", as->argc, *as->argv);
		/* code */
	}
	

	return (SUCCESS);	
}