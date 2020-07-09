/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vm_main.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 19:26:06 by zitzak        #+#    #+#                 */
/*   Updated: 2020/07/09 19:26:14 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl_fd("enter a number", 1);
		return (1);
	}
	some_vm_function(argv[1]);
	return (0);
}
