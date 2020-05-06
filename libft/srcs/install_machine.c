/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   install_machine.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/18 14:08:27 by nstabel       #+#    #+#                 */
/*   Updated: 2020/04/12 14:45:03 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool			install_machine(t_machine **machine, t_state end)
{
	*machine = (t_machine *)ft_memalloc(sizeof(t_machine));
	if (*machine == NULL)
		return (FAIL);
	(*machine)->size = end;
	(*machine)->transition = SUCCESS;
	return (SUCCESS);
}
