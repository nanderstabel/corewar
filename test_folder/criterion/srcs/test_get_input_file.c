/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_get_input_file.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/11 15:34:18 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/22 17:51:25 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "corewar.h"
#include "libft.h"
#include "asm.h"

// void	redirect_all_stdout(void)
// {
// 	cr_redirect_stdout();
// 	cr_redirect_stderr();
// }


// Test(test_get_input_file, no_file_test)
// {
// 	t_project	*as;
// 	t_bool		ret;

// 	as = (t_project*)ft_memalloc(sizeof(t_project));
// 	as->argv = (char**)malloc(sizeof(char*) * 1);
// 	as->argv[0] = ft_strdup("425.s");
// 	ret = get_input_file(as);
// 	// ft_printf("1Can't read source file valid_asm/42.s\n");
// 	// cr_assert_stdout_eq_str("Can't read source file valid_asm/425.s\n");
// 	cr_assert(ret == FAIL);
// }

// Test(test_get_input_file, invalid1_test)
// {
// 	t_project	*as;
// 	t_bool		ret;

// 	as = (t_project*)ft_memalloc(sizeof(t_project));
// 	as->argv = (char**)malloc(sizeof(char*) * 1);
// 	as->argv[0] = ft_strdup(".s");
// 	ret = get_input_file(as);
// 	// ft_printf("1Can't read source file valid_asm/42.s\n");
// 	// cr_assert_stdout_eq_str("Can't read source file valid_asm/425.s\n");
// 	cr_assert(ret == FAIL);
// }

// Test(test_get_input_file, invalid_extension_test)
// {
// 	t_project	*as;
// 	t_bool		ret;

// 	(void)ret;
// 	as = (t_project*)ft_memalloc(sizeof(t_project));
// 	as->argv = (char**)malloc(sizeof(char*) * 1);
// 	as->argv[0] = ft_strdup("valid_asm/425.f");
// 	ret = get_input_file(as);
// 	// ft_printf("1Can't read source file valid_asm/42.s\n");
// // 	cr_assert_stdout_eq_str("Usage: ./asm [-agul] <sourcefile.s>\n\t-a : Instead of creating a .cor file, outputs a stripped and
// // annotated version of the code to the standard output\n\"\t-g : Debug mode: shows executed functions in chronological order\n\t-u : Shows usage message\n");
// 	cr_assert(ret == FAIL);
// }

// Test(test_get_input_file, invalid_extension1_test)
// {
// 	t_project	*as;
// 	t_bool		ret;

// 	(void)ret;
// 	as = (t_project*)ft_memalloc(sizeof(t_project));
// 	as->argv = (char**)malloc(sizeof(char*) * 1);
// 	as->argv[0] = ft_strdup("valid_asm/425");
// 	ret = get_input_file(as);
// 	// ft_printf("1Can't read source file valid_asm/42.s\n");
// // 	cr_assert_stdout_eq_str("Usage: ./asm [-agul] <sourcefile.s>\n\t-a : Instead of creating a .cor file, outputs a stripped and
// // annotated version of the code to the standard output\n\"\t-g : Debug mode: shows executed functions in chronological order\n\t-u : Shows usage message\n");
// 	cr_assert(ret == FAIL);
// }

// Test(test_get_input_file, valid_test)
// {
// 	t_project	*as;
// 	t_bool		ret;

// 	as = (t_project*)ft_memalloc(sizeof(t_project));
// 	as->argv = (char**)malloc(sizeof(char*) * 1);
// 	as->argv[0] = ft_strdup("valid_asm/42.s");
// 	ret = get_input_file(as);
// 	// ft_printf("1Can't read source file valid_asm/42.s\n");
// 	// cr_assert_stdout_eq_str("Can't read source file valid_asm/425.s\n");
// 	cr_assert(ret == SUCCESS);
// }