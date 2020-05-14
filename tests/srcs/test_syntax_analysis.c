/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_syntax_analysis.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 17:56:32 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/14 18:00:35 by nstabel       ########   odam.nl         */
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

Test(test_syntax_analysis, syntax_check_test, .init=redirect_all_stdout2)
{
	t_project	*as = (t_project *)ft_memalloc(sizeof(t_project));
	int			current;
	int			next;
	char		*error;
	t_bool		ret;

	current = INDIRECT_LABEL;
	while (current <= INDIRECT_LABEL)
	{
		next = INDIRECT_LABEL;
		while (next <= INDIRECT_LABEL)
		{
			error  = malloc(100);
			ADD_TOKEN(0, TRAIL, ":l1");
			ADD_TOKEN(0, current, ":l1");
			ADD_TOKEN(0, next, ft_itoa(current));
			as->trail = as->tmp;
			SET_CURRENT_TOKEN;
			SET_NEXT_TOKEN;
			ret = syntax_check(as);
			if (ret == FAIL)
			{
				cr_assert((ret == FAIL));
				FORMAT_SYNTAX_ERR(ft_itoa(current));
				// ft_printf(error);
				cr_assert_stdout_eq_str(error);
				fflush(stdout);
			}
			else
				cr_assert((ret == SUCCESS));
			as->tmp = NULL;
			free(error);
			++next;
		}
		++current;
	}
}



































	
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, COMMAND_NAME, ft_strdup(".name")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, STRING, ft_strdup("JimmyJoy")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, ENDLINE, ft_strdup("\n")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, COMMAND_COMMENT, ft_strdup(".comment")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, STRING, ft_strdup("My name is Jimmy")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, ENDLINE, ft_strdup("\n")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, LABEL, ft_strdup("label1:")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, ENDLINE, ft_strdup("\n")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, INSTRUCTION, ft_strdup("live")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, DIRECT, ft_strdup("%5")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, ENDLINE, ft_strdup("\n")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, LABEL, ft_strdup("label2:")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, INSTRUCTION, ft_strdup("andv")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, DIRECT, ft_strdup("%2")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, SEPARATOR, ft_strdup(",")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, DIRECT_LABEL, ft_strdup("%:l1")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, SEPARATOR, ft_strdup(",")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, REGISTER, ft_strdup("r1")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, ENDLINE, ft_strdup("\n")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, LABEL, ft_strdup("label3:")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, INSTRUCTION, ft_strdup("sub")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, REGISTER, ft_strdup("r1")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, SEPARATOR, ft_strdup(",")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, REGISTER, ft_strdup("r2")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, SEPARATOR, ft_strdup(",")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, REGISTER, ft_strdup("r3")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, ENDLINE, ft_strdup("\n")), 0));
	// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, END, ft_strdup("")), 0));