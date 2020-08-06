/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 17:49:58 by zitzak        #+#    #+#                 */
/*   Updated: 2020/07/29 10:40:34 by mgross        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include "asm.h"

int		main()
{
	// ft_printf("test");
	char  *old;

	old = ft_strdup("dit is een ");
	old = ft_catprintf(old, "test nummer 10 + %d",  5);
	ft_printf("%s\n", old);

	
	
	
	
	return (0);
}