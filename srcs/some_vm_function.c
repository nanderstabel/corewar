/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   some_vm_function.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 19:25:38 by zitzak        #+#    #+#                 */
/*   Updated: 2020/07/09 19:25:55 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	some_vm_function(char *s)
{
	if (ft_isint(s))
		ft_printf("%s is an integer\n", s);
	else
		ft_printf("%s is not an integer\n", s);
}
