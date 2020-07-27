/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_label_check.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 17:56:32 by nstabel       #+#    #+#                 */
/*   Updated: 2020/07/07 13:13:46 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include "corewar.h"
#include "libft.h"
#include "asm.h"

void redirect_all_stdout5(void)
{
        cr_redirect_stdout();
        cr_redirect_stderr();
}

Test(test_label_check, label_check_err1_test, .init=redirect_all_stdout5)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("test_folder/asm_test_folder/invalid_s_files/no_label_error_01.s", O_RDONLY);
	analyze_lexicon(as);
	analyze_syntax(as);
	analyze_instructions(as);
	analyze_parameters(as);	
	ret = translate_to_byte(as);
	cr_assert((ret == FAIL));
	cr_assert_stderr_eq_str("No such label l4 while attempting to dereference token [TOKEN][005:009] INDIRECT_LABEL \":l4\"\n");
}

Test(test_label_check, label_check_err2_test, .init=redirect_all_stdout5)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("test_folder/asm_test_folder/invalid_s_files/no_label_error_02.s", O_RDONLY);
	analyze_lexicon(as);
	analyze_syntax(as);
	analyze_instructions(as);
	analyze_parameters(as);	
	ret = translate_to_byte(as);
	cr_assert((ret == FAIL));
	cr_assert_stderr_eq_str("No such label l4 while attempting to dereference token [TOKEN][005:009] INDIRECT_LABEL \":l4\"\n");
}

Test(test_label_check, label_check_err3_test, .init=redirect_all_stdout5)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("test_folder/asm_test_folder/invalid_s_files/no_label_error_03.s", O_RDONLY);
	analyze_lexicon(as);
	analyze_syntax(as);
	analyze_instructions(as);
	analyze_parameters(as);	
	ret = translate_to_byte(as);
	cr_assert((ret == FAIL));
	cr_assert_stderr_eq_str("No such label toto while attempting to dereference token [TOKEN][053:013] DIRECT_LABEL \"\%:toto\"\n");
}

Test(test_label_check, label_check_err4_test, .init=redirect_all_stdout5)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("test_folder/asm_test_folder/invalid_s_files/no_label_error_04.s", O_RDONLY);
	analyze_lexicon(as);
	analyze_syntax(as);
	analyze_instructions(as);
	analyze_parameters(as);	
	ret = translate_to_byte(as);
	cr_assert((ret == FAIL));
	cr_assert_stderr_eq_str("No such label l4 while attempting to dereference token [TOKEN][005:009] INDIRECT_LABEL \":l4\"\n");
}

Test(test_label_check, label_check_err5_test, .init=redirect_all_stdout5)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("test_folder/asm_test_folder/invalid_s_files/no_label_error_05.s", O_RDONLY);
	analyze_lexicon(as);
	analyze_syntax(as);
	analyze_instructions(as);
	analyze_parameters(as);	
	ret = translate_to_byte(as);
	cr_assert((ret == FAIL));
	cr_assert_stderr_eq_str("No such label l4 while attempting to dereference token [TOKEN][005:009] INDIRECT_LABEL \":l4\"\n");
}
