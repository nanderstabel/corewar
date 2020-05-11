/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_get_input_file.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/11 15:34:18 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/11 15:54:30 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "corewar.h"
#include "libft.h"
#include "asm.h"

Test(test_get_input_file, no_extension)
{
	t_project	*as;

	as = (t_project*)ft_memalloc(sizeof(t_project));
}