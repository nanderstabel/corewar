/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_lexicon_utils2.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 15:19:56 by nstabel       #+#    #+#                 */
/*   Updated: 2020/08/07 15:21:29 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** ---------------------------------------------------------------------------**
** The (label_or_instruction_token) function redirects to either the label_token
** function or to the instruction_token function.
** Otherwise it's a lexical error.
**
** t_project 	*as		  =	struct of type t_project. olds all data for the asm
** char			**line	  =	points current place in the line
**
** return 		(SUCCESS) =	element is added to the list as->token_list
** return		 (FAIL)	  = lexical error is found
*/

t_bool			label_or_instruction_token(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	if (!is_valid_label_chars(as, line))
	{
		if (**line == LABEL_CHAR)
			label_token(as, line);
		else
			return (FAIL);
	}
	else
	{
		instruction_token(as, line);
	}
	return (SUCCESS);
}

/*
** ---------------------------------------------------------------------------**
** The (label_chars_redirect) function redirects to either register_token func-
** tion, indirect_token function or to another sorting function named
** label_or_instruction function. If one of the functions it redirects to return
** FAIL it's a lexical error.
**
** t_project 	*as		  =	struct of type t_project. olds all data for the asm
** char			**line	  =	points current place in the line
**
** return 		(SUCCESS) =	element is added to the list as->token_list
** return		 (FAIL)	  = lexical error is found
*/

t_bool			label_chars_redirect(t_project *as, char **line)
{
	int			index;

	index = 0;
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	if (**line == 'r')
	{
		while (ft_isdigit((int)(*line)[index + 1]))
			index++;
		if (index <= TWO_DIGITS &&
		ft_strchr(END_LABEL_CHARS, *((*line) + index + 1)))
		{
			if (!register_token(as, line))
				return (FAIL);
			return (SUCCESS);
		}
		index = 0;
	}
	while (ft_isdigit((int)(*line)[index]))
		index++;
	if (index > 0 && ft_strchr(END_LABEL_CHARS, *((*line) + index)))
		indrect_token(as, line);
	else if (!label_or_instruction_token(as, line))
		return (FAIL);
	return (SUCCESS);
}

void			add_strings(t_project *as, char **line)
{
	char		*final_string;
	char		*str_temp;

	str_temp = ft_strchr(*line, (int)'"');
	final_string = as->string;
	if (!(str_temp - *line))
		str_temp = ft_strnew(0);
	else
		str_temp = ft_strndup(*line, (str_temp - *line));
	increment_line(as, line, ft_strlen(str_temp) + 1);
	as->string = ft_strjoin(as->string, str_temp);
	free(str_temp);
	free(final_string);
}

int				newline_string_token(t_project *as, char **line)
{
	char		*str_temp;
	char		*temp;

	as->string = ft_strnew(0);
	str_temp = ft_strchr(*line, (int)'"');
	while (!str_temp)
	{
		temp = as->string;
		as->string = ft_strjoin(as->string, *line);
		if (as->og_line != NULL)
			free(as->og_line);
		if (!get_next_endline(as->fd, line))
			return (FAIL);
		as->og_line = *line;
		as->row++;
		free(temp);
		str_temp = ft_strchr(*line, (int)'"');
	}
	add_strings(as, line);
	return (SUCCESS);
}

t_bool			string_token2(t_project *as, char **line, int len,
				char *str_temp)
{
	if (!str_temp)
	{
		if (!newline_string_token(as, line))
			return (FAIL);
		ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
		(as->column - (*line - as->temp)), STRING, as->string),
		sizeof(t_token)));
		as->count =
		(as->flags & DEBUG_L) ? ft_printf("--add STRING token\n") : 0;
	}
	else
	{
		ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
		(as->column - (*line - as->temp)), STRING, ft_strndup(as->temp + 1,
		len - 1)), sizeof(t_token)));
		as->count =
		(as->flags & DEBUG_L) ? ft_printf("--add STRING token\n") : 0;
		increment_line(as, line, len);
	}
	return (SUCCESS);
}
