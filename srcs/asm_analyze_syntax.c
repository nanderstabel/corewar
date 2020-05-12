/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_analyze_syntax.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/12 21:18:49 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool			syntax_check(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	if (token_tab[as->current_token->token_type].next[as->next_token->token_type])
		ft_printf("\t%s --> %s\n", token_tab[as->current_token->token_type].string, token_tab[as->next_token->token_type].string);
	else
	{
		ft_printf(SYNTAX_ERR ERROR_FORMAT, as->next_token->row, as->next_token->column, token_tab[as->next_token->token_type].string, as->next_token->literal_str);
		return (FAIL);
	}
	return (SUCCESS);
}

t_bool			analyze_syntax(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, COMMAND_NAME, ".name"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, STRING, "JimmyJoy"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, ENDLINE, "\n"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, COMMAND_COMMENT, ".comment"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, STRING, "My name is Jimmy"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, ENDLINE, "\n"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, LABEL, "l1:"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, ENDLINE, "\n"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, INSTRUCTION, "live"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, REGISTER, "r1"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, ENDLINE, "\n"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, INSTRUCTION, "addp"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, DIRECT, "%2"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, SEPARATOR, ","), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, DIRECT, "%2"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, SEPARATOR, ","), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, DIRECT_LABEL, "%:l1"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, SEPARATOR, ","), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, INDIRECT, "5"), 0));
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((const void *)new_token(as, ENDLINE, "\n"), 0));

	return (loop_token_list(as, syntax_check));
}
