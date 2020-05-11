/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_get_input_file.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/11 15:34:18 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/11 19:17:33 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "corewar.h"
#include "libft.h"
#include "asm.h"

Test(test_get_input_file, tes)
{
	t_project	*as;
	// t_bool		ret;

	as = (t_project*)ft_memalloc(sizeof(t_project));
	as->argv = (char**)malloc(sizeof(char*) * 1);
	as->argv[0] = ft_strdup("42.s");
	 get_input_file(as);
	// cr_assert(ret == SUCCESS);
}