/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_syntax_analysis.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 17:56:32 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/15 04:12:33 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include "corewar.h"
#include "libft.h"
#include "asm.h"

# define ADD_TOKEN(y_axis, type, str)	ft_lstadd_back(&as->tmp, ft_lstnew_ptr((const void *)new_token(as, (y_axis), (type), ft_strdup((str))), 0))
# define CURRENT_TOKEN					as->current_token
# define NEXT_TOKEN						as->next_token
# define SET_CURRENT_TOKEN				CURRENT_TOKEN = (t_token *)as->tmp->next->content
# define SET_NEXT_TOKEN					NEXT_TOKEN = (t_token *)as->tmp->next->next->content
# define FORMAT_SYNTAX_ERR(str0)		sprintf(error, "Syntax error at token [TOKEN][000:000] %s \"%s\"\n", token_tab[next].string, str0)
# define TRAIL							END + 1

void redirect_all_stdout2(void)
{
        cr_redirect_stdout();
        cr_redirect_stderr();
}

// Test(test_syntax_analysis, syntax_check_test, .init=redirect_all_stdout2)
// {
// 	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
// 	int			current;
// 	int			next;
// 	char		*error;
// 	t_bool		ret;

// 	current = INDIRECT_LABEL;
// 	while (current <= INDIRECT_LABEL)
// 	{
// 		next = INDIRECT_LABEL;
// 		while (next <= INDIRECT_LABEL)
// 		{
// 			error  = malloc(100);
// 			ADD_TOKEN(0, TRAIL, ":l1");
// 			ADD_TOKEN(0, current, ":l1");
// 			ADD_TOKEN(0, next, ft_itoa(current));
// 			as->trail = as->tmp;
// 			SET_CURRENT_TOKEN;
// 			SET_NEXT_TOKEN;
// 			ret = syntax_check(as);
// 			if (ret == FAIL)
// 			{
// 				cr_assert((ret == FAIL));
// 				FORMAT_SYNTAX_ERR(ft_itoa(current));
// 				// ft_printf(error);
// 				cr_assert_stdout_eq_str(error);
// 				fflush(stdout);
// 			}
// 			else
// 				cr_assert((ret == SUCCESS));
// 			as->tmp = NULL;
// 			free(error);
// 			++next;
// 		}
// 		++current;
// 	}
// }

Test(test_syntax_analysis, syntax_analysis_err1_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_error_01.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == FAIL));
	cr_assert_stdout_eq_str("Syntax error at token [TOKEN][008:010] INDIRECT_LABEL \":l2\"\n");
}

Test(test_syntax_analysis, syntax_analysis_err2_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_error_02.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == FAIL));
	cr_assert_stdout_eq_str("Syntax error at token [TOKEN][012:018] INDIRECT \"100\"\n");
}

Test(test_syntax_analysis, syntax_analysis_err3_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_error_03.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == FAIL));
	cr_assert_stdout_eq_str("Syntax error at token [TOKEN][003:001] COMMAND_COMMENT \".comment\"\n");
}

Test(test_syntax_analysis, syntax_analysis_err4_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_error_04.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == FAIL));
	cr_assert_stdout_eq_str("Syntax error at token [TOKEN][003:001] COMMAND_NAME \".name\"\n");
}

Test(test_syntax_analysis, syntax_analysis_err6_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_error_06.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == FAIL));
	cr_assert_stdout_eq_str("Syntax error at token [TOKEN][008:016] INDIRECT \"-44\"\n");
}

Test(test_syntax_analysis, syntax_analysis_err7_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_error_07.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == FAIL));
	cr_assert_stdout_eq_str("Syntax error at token [TOKEN][078:007] INSTRUCTION \"x0370044\"\n");
}

Test(test_syntax_analysis, syntax_analysis_err8_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_error_08.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == FAIL));
	cr_assert_stdout_eq_str("Syntax error at token [TOKEN][007:021] ENDLINE\n");
}

Test(test_syntax_analysis, syntax_analysis_err9_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_error_09.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == FAIL));
	cr_assert_stdout_eq_str("Syntax error at token [TOKEN][007:021] INSTRUCTION \"st\"\n");
}

Test(test_syntax_analysis, syntax_analysis_err10_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_error_10.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == FAIL));
	cr_assert_stdout_eq_str("Syntax error at token [TOKEN][007:022] INSTRUCTION \"st\"\n");
}

Test(test_syntax_analysis, syntax_analysis_err11_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_error_11.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == FAIL));
	cr_assert_stdout_eq_str("Syntax error at token [TOKEN][007:021] LABEL \"test:\"\n");
}

Test(test_syntax_analysis, syntax_analysis_err12_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_error_12.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == FAIL));
	cr_assert_stdout_eq_str("Syntax error at token [TOKEN][070:007] INSTRUCTION \"live\"\n");
}

Test(test_syntax_analysis, syntax_analysis_err13_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_error_13.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == FAIL));
	cr_assert_stdout_eq_str("Syntax error at token [TOKEN][002:001] END \"(null)\"\n");
}

Test(test_syntax_analysis, syntax_analysis_err15_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_error_15.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == FAIL));
	cr_assert_stdout_eq_str("Syntax error - unexpected end of input (Perhaps you forgot to end with a newline ?)\n");
}

Test(test_syntax_analysis, syntax_analysis_err16_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_error_16.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == FAIL));
	cr_assert_stdout_eq_str("Syntax error at token [TOKEN][004:007] END \"(null)\"\n");
}

Test(test_syntax_analysis, syntax_analysis_no_label1_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/no_label_error_01.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == SUCCESS));
}

Test(test_syntax_analysis, syntax_analysis_no_label2_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/no_label_error_02.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == SUCCESS));
}

Test(test_syntax_analysis, syntax_analysis_no_label3_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/no_label_error_03.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == SUCCESS));
}

Test(test_syntax_analysis, syntax_analysis_parameter1_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/parameter_error_01.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == SUCCESS));
}

Test(test_syntax_analysis, syntax_analysis_parameter2_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/parameter_error_02.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == SUCCESS));
}

Test(test_syntax_analysis, syntax_analysis_parameter3_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/parameter_error_03.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == SUCCESS));
}

Test(test_syntax_analysis, syntax_analysis_break1_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_break01.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == SUCCESS));
}

Test(test_syntax_analysis, syntax_analysis_break2_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_break02.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == SUCCESS));
}

Test(test_syntax_analysis, syntax_analysis_break3_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_break03.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == SUCCESS));
}

Test(test_syntax_analysis, syntax_analysis_break4_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_break04.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == SUCCESS));
}

Test(test_syntax_analysis, syntax_analysis_break5_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_break05.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == SUCCESS));
}

Test(test_syntax_analysis, syntax_analysis_break6_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_break06.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == SUCCESS));
}

Test(test_syntax_analysis, syntax_analysis_break7_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_break07.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == SUCCESS));
}

Test(test_syntax_analysis, syntax_analysis_break8_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	t_bool		ret;

	as->fd = open("./invalid_asm/syntax_break08.s", O_RDONLY);
	analyze_lexicon(as);	
	ret = analyze_syntax(as);
	cr_assert((ret == SUCCESS));
}
