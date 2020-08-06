/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_instruction_analysis.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 17:56:32 by nstabel       #+#    #+#                 */
/*   Updated: 2020/07/06 17:13:35 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include "corewar.h"
#include "libft.h"
#include "asm.h"

void redirect_all_stdout3(void)
{
        cr_redirect_stdout();
        cr_redirect_stderr();
}

Test(test_instruction_analysis, instruction_analysis_err1_test, .init=redirect_all_stdout3)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/invalid_instruction_error_01.s", O_RDONLY);
	analyze_lexicon(as);	
	analyze_syntax(as);
	ret = analyze_instructions(as);
	cr_assert((ret == FAIL));
	cr_assert_stderr_eq_str("Invalid instruction at token [TOKEN][006:002] INSTRUCTION \"ld50\"\n");
}

Test(test_instruction_analysis, instruction_analysis_break1_test, .init=redirect_all_stdout3)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/instruction_break01.s", O_RDONLY);
	analyze_lexicon(as);	
	analyze_syntax(as);
	ret = analyze_instructions(as);
	cr_assert((ret == SUCCESS));
}
