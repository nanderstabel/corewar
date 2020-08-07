/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_lexicon_utils1.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 15:19:49 by nstabel       #+#    #+#                 */
/*   Updated: 2020/08/07 15:21:09 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** ---------------------------------------------------------------------------**
** The (command_token) function checks if the string is a
** valid COMMAND token (until whitespaces & deliminator). If so a link is
** added to the link list. If not it is a lexical error.
**
** t_project 	*as		  =	struct of type t_project. Holds all data for the asm
** char			**line	  =	points current place in the line
**
** return 		(SUCCESS) =	element is added to the list as->token_list
** return 		(FAIL)	  =	lexical error is found
*/

t_bool			command_token(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	if (ft_strequ_wspace_delim(*line, ".name"))
	{
		ft_lstadd_back(&as->token_list,
		ft_lstnew_ptr((void*)new_token(as, as->column,
		COMMAND_NAME, ft_strdup(".name")), sizeof(t_token)));
		increment_line(as, line, 5);
		as->count =
		(as->flags & DEBUG_L) ? ft_printf("--add COMMAND_NAME token\n") : 0;
	}
	else if (ft_strequ_wspace_delim(*line, ".comment"))
	{
		ft_lstadd_back(&as->token_list,
		ft_lstnew_ptr((void*)new_token(as, as->column,
		COMMAND_COMMENT, ft_strdup(".comment")), sizeof(t_token)));
		increment_line(as, line, 8);
		as->count =
		(as->flags & DEBUG_L) ? ft_printf("--add COMMAND_COMMENT token\n") : 0;
	}
	else
		return (FAIL);
	return (SUCCESS);
}

/*
** ---------------------------------------------------------------------------**
** The (register_token) function checks if it's a valid REGISTER token.
**  If valid a link is added to the link list. If not it is a lexical error.
**
** t_project 	*as		  =	struct of type t_project. olds all data for the asm
** char			**line	  =	points current place in the line
**
** return 		(SUCCESS) =	element is added to the list as->token_list
** return		 (FAIL)	  = lexical error is found
*/

t_bool			register_token(t_project *as, char **line)
{
	int			increment;

	increment = 1;
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	increment_line(as, line, 1);
	if ((**line == '0' && ft_strchr(END_LABEL_CHARS, *((*line) + 1))) ||
	(**line == '0' && *((*line) + 1) == '0'))
	{
		if (*((*line) + 1) == '0')
			increment_line(as, line, 1);
		return (FAIL);
	}
	if (ft_isdigit((int)*((*line) + 1)))
		increment++;
	increment_line(as, line, increment);
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
	(as->column - (*line - as->temp)), REGISTER, ft_strndup(as->temp,
	(*line - as->temp))), sizeof(t_token)));
	as->count = (as->flags & DEBUG_L) ? ft_printf("--add REGISTER token\n") : 0;
	return (SUCCESS);
}

/*
** ---------------------------------------------------------------------------**
** The (is_valid_label_chars) function loops through *line until END_LABEL_CHARS
** are found or a char is not part of LABEL_CHARS.
**
** t_project 	*as		  =	struct of type t_project. olds all data for the asm
** char			**line	  =	points current place in the line
**
** return 		(SUCCESS) =	element is added to the list as->token_list
** return		 (FAIL)	  = lexical error is found
*/

t_bool			is_valid_label_chars(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	while (!ft_strchr(END_LABEL_CHARS, **line) && (**line) && **line != '-')
	{
		if (!ft_strchr(LABEL_CHARS, **line))
		{
			return (FAIL);
		}
		increment_line(as, line, 1);
	}
	return (SUCCESS);
}

/*
** ---------------------------------------------------------------------------**
** The (instruction_token) function stores a INSTRUCTION token in the list.
**
** t_project 	*as		  =	struct of type t_project. olds all data for the asm
** char			**line	  =	points current place in the line
*/

void			instruction_token(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	as->count =
	(as->flags & DEBUG_L) ? ft_printf("--add INSTRUCTION token\n") : 0;
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
	(as->column - (*line - as->temp)), INSTRUCTION, ft_strndup(as->temp,
	(*line - as->temp))), sizeof(t_token)));
}

/*
** ---------------------------------------------------------------------------**
** The (label_token) function stores a LABEL token in the list.
**
** t_project 	*as		  =	struct of type t_project. olds all data for the asm
** char			**line	  =	points current place in the line
*/

void			label_token(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	increment_line(as, line, 1);
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
	(as->column - (*line - as->temp)), LABEL, ft_strndup(as->temp,
	(*line - as->temp))), sizeof(t_token)));
	as->count =
	(as->flags & DEBUG_L) ? ft_printf("--add LABEL token\n") : 0;
}
