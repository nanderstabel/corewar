/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_analyze_syntax.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/14 21:53:03 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool			syntax_error(t_project *as)
{
	ft_printf(SYNTAX_ERR);
	if (as->next_token->token_type == ENDLINE)
		ft_printf(ENDLINE_FORMAT, as->next_token->row + 1, \
		as->next_token->column + 1, token_tab[as->next_token->token_type].string);
	else
		ft_printf(ERROR_FORMAT, as->next_token->row + 1, \
		as->next_token->column + 1, token_tab[as->next_token->token_type].string, \
		as->next_token->literal_str);
	return (FAIL);
}

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
	else if (as->next_token->token_type == END && !(as->name_found && as->comment_found))
		return (syntax_error(as));
	return (SUCCESS);
}

/*
** -------------------------------------------------------------------------- **
** checks if the current token and the next token are a valid sequence using
** the token_tab table. If it's not valid, it prints an error message and
** returns FAIL. If the current token is of type SEPARATOR, this node gets
** deleted since this token type is not needed anymore. This function is used
** as an argument for the loop_token_list function.
** params
**	as->current_token	the current token
**	as->next_token		the next token
**	token_tab			table with valid sequences
**	as->tmp				holds current position in as->token_list
**	as->trail			holds previous position in as->token_list
** return
**	SUCCESS		in case the sequence is valid
**	FAIL		in case the sequence is invalid
*/

t_bool			syntax_check(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	if (command_syntax_check(as) == FAIL)
		return (FAIL);
	if (!token_tab[as->current_token->token_type].\
		next[as->next_token->token_type])
		return (syntax_error(as));
	if (as->current_token->token_type == SEPARATOR)
	{
		as->tmp = as->trail;
		//add del_token_node here
		as->tmp->next = as->tmp->next->next;
	}
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
**	SUCCESS		in case the syntax analysis was successful
**	FAIL		in case the syntax analysis failed
*/

t_bool			analyze_syntax(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	while (as->token_list)
	{
		ft_printf("token: %s\n", token_tab[((t_token *)as->token_list->content)->token_type].string);
		as->token_list = as->token_list->next;
	}
	return (loop_token_list(as, syntax_check));
}
