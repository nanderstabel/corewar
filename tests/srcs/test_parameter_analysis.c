/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_parameter_analysis.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 01:47:31 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/15 02:39:03 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include "corewar.h"
#include "libft.h"
#include "asm.h"

void redirect_all_stdout4(void)
{
        cr_redirect_stdout();
        cr_redirect_stderr();
}

Test(test_parameter_analysis, parameter_analysis_err1_test, .init=redirect_all_stdout4)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/parameter_error_01.s", O_RDONLY);
	analyze_lexicon(as);	
	analyze_syntax(as);
	analyze_instructions(as);
	ret = analyze_parameters(as);
	cr_assert((ret == FAIL));
	cr_assert_stdout_eq_str("Invalid parameter 1 type indirect for instruction ld\n");
}

Test(test_parameter_analysis, parameter_analysis_err2_test, .init=redirect_all_stdout4)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/parameter_error_02.s", O_RDONLY);
	analyze_lexicon(as);	
	analyze_syntax(as);
	analyze_instructions(as);
	ret = analyze_parameters(as);
	cr_assert((ret == FAIL));
	cr_assert_stdout_eq_str("Invalid parameter 2 type indirect for instruction ld\n");
}

Test(test_parameter_analysis, parameter_analysis_err3_test, .init=redirect_all_stdout4)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/parameter_error_03.s", O_RDONLY);
	analyze_lexicon(as);	
	analyze_syntax(as);
	analyze_instructions(as);
	ret = analyze_parameters(as);
	cr_assert((ret == FAIL));
	cr_assert_stdout_eq_str("Invalid parameter 2 type indirect for instruction sti\n");
}

Test(test_parameter_analysis, parameter_analysis_err4_test, .init=redirect_all_stdout4)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/parameter_error_04.s", O_RDONLY);
	analyze_lexicon(as);	
	analyze_syntax(as);
	analyze_instructions(as);
	ret = analyze_parameters(as);
	cr_assert((ret == FAIL));
	cr_assert_stdout_eq_str("Invalid parameter 0 type register for instruction live\n");
}

Test(test_parameter_analysis, parameter_analysis_err5_test, .init=redirect_all_stdout4)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/parameter_error_05.s", O_RDONLY);
	analyze_lexicon(as);	
	analyze_syntax(as);
	analyze_instructions(as);
	ret = analyze_parameters(as);
	cr_assert((ret == FAIL));
	cr_assert_stdout_eq_str("Invalid parameter 0 type direct for instruction add\n");
}
