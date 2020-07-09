/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_analyze_syntax.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/07/09 18:33:25 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** -------------------------------------------------------------------------- **
** if during the syntax analysis an invalid sequence is found, this function
** prints the corresponding error message. First it checks for an unexpected
** end of the token_list. If not, it prints the generic SYNTAX_ERR with
** ENDLINE_FORMAT if next token type is ENDLINE, and else with the ERROR_FORMAT
** params
**	as->next_token		the next token
**	token_tab			table with valid sequences
** return
**	FAIL				in case the sequence is invalid
*/

t_bool			syntax_error(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	if (as->next_token->token_type == END && as->header_found && \
		as->current_token->token_type != LABEL)
	{
		ft_dprintf(2, UNEXPECTED_END);
		return (FAIL);
	}
	ft_dprintf(2, SYNTAX_ERR);
	if (as->next_token->token_type == ENDLINE)
		ft_dprintf(2, ENDLINE_FORMAT, as->next_token->row + 1, \
		as->next_token->column + 1, \
		g_token_tab[as->next_token->token_type].string);
	else if (as->next_token->token_type == STRING)
		ft_dprintf(2, STRING_FORMAT, as->next_token->row + 1, \
		as->next_token->column + 1, \
		g_token_tab[as->next_token->token_type].string, \
		as->next_token->literal_str);
	else
		ft_dprintf(2, ERROR_FORMAT, as->next_token->row + 1, \
		as->next_token->column + 1, \
		g_token_tab[as->next_token->token_type].string, \
		as->next_token->literal_str);
	return (FAIL);
}

/*
** -------------------------------------------------------------------------- **
** first checks if the current token is of type COMMAND_NAME or COMMAND_NAME.
** If so, the corresponding variables are updated. Then it will return
** syntax_error if the next token type is COMMAND_NAME or COMMAND_COMMENT AND
** if these tokens are already found. As a final check it checks whether the
** next token is of type END AND COMMAND_NAME AND COMMAND_COMMENT ar not yet
** found. If so, syntax_error is returned.
** params
**	as->current_token	the current token
**	as->next_token		the next token
** return
**	SUCCESS				in case the sequence is valid
**	syntax_error(as)	in case an error message is printed (== FAIL)
*/

t_bool			command_syntax_check(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	if (as->current_token->token_type == COMMAND_NAME)
		++as->name_found;
	else if (as->current_token->token_type == COMMAND_COMMENT)
		++as->comment_found;
	if (as->next_token->token_type == COMMAND_NAME && as->name_found)
		return (syntax_error(as));
	else if (as->next_token->token_type == COMMAND_COMMENT && as->comment_found)
		return (syntax_error(as));
	else if (as->next_token->token_type == END && \
		!(as->name_found && as->comment_found))
		return (syntax_error(as));
	return (SUCCESS);
}

/*
** -------------------------------------------------------------------------- **
** this check is performed to determine if the header is already found. If so,
** SUCCESS is returned. Else, if the next token is of type LABEL or INSTRUCTION
** this means the header is found. If the header is incomplete though, current
** token type is set to END to trigger a syntax_error in syntax_check. If the
** header is complete, header_found is set to SUCCESS and SUCCESS is returned.
** IF the header is not found AND next token type is not LABEL and not
** INSTRUCTION, then FAIL is returned.
** params
**	as->current_token	the current token
**	as->next_token		the next token
**	as->name_found		determines if name is found
**	as->comment_found	determines if comment is found
**	as->header_found	determines if header is found
** return
**	SUCCESS				if header is found
**	FAIL				if header is not found
*/

t_bool			find_header(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	if (as->header_found)
		return (SUCCESS);
	if (as->next_token->token_type == LABEL || \
		as->next_token->token_type == INSTRUCTION)
	{
		if (!as->name_found || !as->comment_found)
		{
			as->current_token->token_type = END;
			return (FAIL);
		}
		as->header_found = SUCCESS;
		return (SUCCESS);
	}
	return (FAIL);
}

/*
** -------------------------------------------------------------------------- **
** this check is performed to break out of loop_token_list. When the header is
** already found, it checks if the current token type is ENDLINE and then checks
** if the next token type is an argument type, a SEPARATOR or a STRING. If this
** is so, the token_list is cut and FAIL is returned. If current token type is
** not ENDLINE, SUCCESS is returned.
** params
**	as->current_token	the current token
**	as->next_token		the next token
**	as->header_found	determines if header is found
**	as->tmp				the current position in the token_list
** return
**	SUCCESS				no valid break is found
**	FAIL				a valid break is found
*/

t_bool			syntax_break_check(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	if (!as->header_found)
		return (SUCCESS);
	if (as->current_token->token_type == ENDLINE)
		if (is_argument(as->next_token->token_type) || \
			as->next_token->token_type == SEPARATOR || \
			as->next_token->token_type == STRING || \
			as->next_token->token_type == COMMAND_NAME || \
			as->next_token->token_type == COMMAND_COMMENT)
		{
			as->tmp = as->tmp->next;
			as->trail = as->trail->next;
			del_token_list(as);
			end_token(as);
			as->tmp = as->trail->next;
			return (FAIL);
		}
	return (SUCCESS);
}

/*
** -------------------------------------------------------------------------- **
** first checks if the header is already found, if it is not, then it will do
** the command_syntax_check. If this fails, FAIL is returned. Secondly, it
** checks whether the current token type and the next token type are a valid
** sequence. If the sequence is invalid, first the syntax_break_check is
** performed. If this check succeeds, syntax_error is returned, else FAIL.
** If current token type is SEPARATOR, the node is skipped since this token type
** is not needed anymore after the syntax analysis. If all goed well, SUCCESS is
** returned
** params
**	as->current_token	the current token
**	as->next_token		the next token
**	token_tab			table with valid sequences
** return
**	SUCCESS				in case the sequence is valid
**	FAIL				in case the sequence is invalid
**	syntax_error(as)	in case an error message is printed (== FAIL)
*/

t_bool			syntax_check(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	if (find_header(as) == FAIL)
		if (command_syntax_check(as) == FAIL)
			return (FAIL);
	if (!g_token_tab[as->current_token->token_type].\
		next[as->next_token->token_type])
	{
		if (syntax_break_check(as) == FAIL)
			return (FAIL);
		return (syntax_error(as));
	}
	else
		syntax_break_check(as);
	if (as->current_token->token_type == SEPARATOR)
		del_token_node(as);
	return (SUCCESS);
}

/*
** -------------------------------------------------------------------------- **
** this is the main function for the syntax analysis. It gives syntax_check
** as an argument to loop_token_list and returns whatever loop_token_list
** returns
** params
**	*as		project struct
** return
**	SUCCESS				in case the syntax analysis was successful
**	FAIL				in case the syntax analysis failed
*/

t_bool			analyze_syntax(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	as->current_token = (t_token *)as->token_list->content;
	as->next_token = (t_token *)as->token_list->content;
	if (as->next_token->token_type != ENDLINE && \
		as->next_token->token_type != COMMAND_NAME && \
		as->next_token->token_type != COMMAND_COMMENT)
		return (syntax_error(as));
	return (loop_token_list(as, syntax_check));
}
