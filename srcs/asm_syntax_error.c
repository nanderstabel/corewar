/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_syntax_error.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 17:49:49 by nstabel       #+#    #+#                 */
/*   Updated: 2020/08/06 17:50:24 by nstabel       ########   odam.nl         */
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
		exit(0);
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
	exit(0);
	return (FAIL);
}
