/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_parameter_analysis.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 01:47:31 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/15 18:48:59 by nstabel       ########   odam.nl         */
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

Test(test_parameter_analysis, encoding_byte1_test)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, INSTRUCTION, "add"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, REGISTER, "%70"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, REGISTER, "r56"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, REGISTER, "90"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, ENDLINE, "\n"), 0));
	as->current_token = (t_token *)as->token_list->content;
	as->current_token->opcode = 4;
	as->current_token->encoding = 1;
	as->next_token = (t_token *)as->token_list->next->content;
	as->tmp = as->token_list;
	parameter_check(as);
	cr_assert(((int)as->current_token->encoding == 0b01010100));
}

Test(test_parameter_analysis, encoding_byte2_test)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, INSTRUCTION, "live"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, DIRECT, "%70"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, ENDLINE, "\n"), 0));
	as->current_token = (t_token *)as->token_list->content;
	as->current_token->opcode = 1;
	as->current_token->encoding = 0;
	as->next_token = (t_token *)as->token_list->next->content;
	as->tmp = as->token_list;
	parameter_check(as);
	cr_assert(((int)as->current_token->encoding == 0b0));
}

Test(test_parameter_analysis, encoding_byte3_test)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, INSTRUCTION, "ld"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, INDIRECT, "70"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, REGISTER, "r56"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, ENDLINE, "\n"), 0));
	as->current_token = (t_token *)as->token_list->content;
	as->current_token->opcode = 2;
	as->current_token->encoding = 1;
	as->next_token = (t_token *)as->token_list->next->content;
	as->tmp = as->token_list;
	parameter_check(as);
	cr_assert(((int)as->current_token->encoding == 0b11010000));
}

Test(test_parameter_analysis, encoding_byte4_test)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));

	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, INSTRUCTION, "and"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, INDIRECT_LABEL, "%70"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, DIRECT, "r56"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, REGISTER, "90"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, ENDLINE, "\n"), 0));
	as->current_token = (t_token *)as->token_list->content;
	as->current_token->opcode = 6;
	as->current_token->encoding = 1;
	as->next_token = (t_token *)as->token_list->next->content;
	as->tmp = as->token_list;
	parameter_check(as);
	cr_assert(((int)as->current_token->encoding == 0b11100100));
}
Test(test_parameter_analysis, encoding_byte5_test)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, INSTRUCTION, "aff"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, REGISTER, "r56"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, ENDLINE, "\n"), 0));
	as->current_token = (t_token *)as->token_list->content;
	as->current_token->opcode = 16;
	as->current_token->encoding = 1;
	as->next_token = (t_token *)as->token_list->next->content;
	as->tmp = as->token_list;
	parameter_check(as);
	cr_assert(((int)as->current_token->encoding == 0b01000000));
}

Test(test_parameter_analysis, encoding_byte6_test)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, INSTRUCTION, "lld"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, DIRECT, "%70"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, REGISTER, "r56"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(new_token(as, 0, ENDLINE, "\n"), 0));
	as->current_token = (t_token *)as->token_list->content;
	as->current_token->opcode = 13;
	as->current_token->encoding = 1;
	as->next_token = (t_token *)as->token_list->next->content;
	as->tmp = as->token_list;
	parameter_check(as);
	cr_assert(((int)as->current_token->encoding == 0b10010000));
}
