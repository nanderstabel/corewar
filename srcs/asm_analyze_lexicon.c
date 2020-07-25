/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_analyze_lexicon.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/07/10 12:02:15 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** ---------------------------------------------------------------------------**
** Look up tabel to match the char where line is on to a function to execute.
*/

t_redirect		g_look_up[] =
{
	{WHITESPACES, skip_whitespaces},
	{"#;", skip_comment_line},
	{".", command_token},
	{"%", direct_token},
	{":", indirect_label_token},
	{LABEL_CHARS, label_chars_redirect},
	{"-", indrect_token},
	{",", separator_token},
	{"\"", string_token}
};

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

t_bool			string_token(t_project *as, char **line)
{
	char		*str_temp;
	int			len;

	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	increment_line(as, line, 1);
	str_temp = ft_strchr(*line, (int)'"');
	len = str_temp - as->temp;
	if (len == 1)
	{
		ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
		(as->column - (*line - as->temp)), STRING, ft_strnew(0)),
		sizeof(t_token)));
		increment_line(as, line, 1);
	}
	else
	{
		if (!string_token2(as, line, len, str_temp))
			return (FAIL);
	}
	return (SUCCESS);
}

t_bool			separator_token(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr(
	(void*)new_token(as, as->column, SEPARATOR,
	ft_strndup(as->temp, 1)), sizeof(t_token)));
	increment_line(as, line, 1);
	as->count =
	(as->flags & DEBUG_L) ? ft_printf("--add SEPARATOR token\n") : 0;
	return (SUCCESS);
}

t_bool			indirect_label_token(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	increment_line(as, line, 1);
	if (ft_strchr(LABEL_CHARS, **line))
	{
		if (!is_valid_label_chars(as, line))
			return (FAIL);
		ft_lstadd_back(&as->token_list, ft_lstnew_ptr(
			(void*)new_token(as, (as->column - (*line - as->temp)),
			INDIRECT_LABEL, ft_strndup(as->temp,
			(*line - as->temp))), sizeof(t_token)));
		as->count =
		(as->flags & DEBUG_L) ? ft_printf("--add INDIRECT_LABEL token\n") : 0;
		return (SUCCESS);
	}
	return (FAIL);
}

t_bool			direct_label_token(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	increment_line(as, line, 1);
	if (!is_valid_label_chars(as, line))
		return (FAIL);
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
	(as->column - (*line - as->temp)), DIRECT_LABEL, ft_strndup(as->temp,
	(*line - as->temp))), sizeof(t_token)));
	as->count =
	(as->flags & DEBUG_L) ? ft_printf("--add DIRECT_LABEL token\n") : 0;
	return (SUCCESS);
}

void			increment_line(t_project *as, char **line, size_t len)
{
	size_t		index;

	index = 0;
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	while (index < len)
	{
		(*line)++;
		as->column++;
		index++;
	}
}

t_bool			indrect_token(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	if (**line == '-' && !ft_isdigit((int)*((*line) + 1)))
		return (FAIL);
	skip_to_end_number(as, line);
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
	(as->column - (*line - as->temp)), INDIRECT, ft_strndup(as->temp,
	(*line - as->temp))), sizeof(t_token)));
	as->count = (as->flags & DEBUG_L) ? ft_printf("--add INDIRECT token\n") : 0;
	return (SUCCESS);
}

void			skip_to_end_number(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	if (**line == '-')
		increment_line(as, line, 1);
	while (ft_isdigit((int)**line))
		increment_line(as, line, 1);
}

t_bool			direct_token(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	if (ft_strchr(END_LABEL_CHARS, *(*line + 1)))
		return (FAIL);
	increment_line(as, line, 1);
	if (**line == ':')
	{
		increment_line(as, line, 1);
		if (!direct_label_token(as, line))
			return (FAIL);
	}
	else
	{
		if (!ft_isdigit((int)**line) && **line != '-')
			return (FAIL);
		else
		{
			skip_to_end_number(as, line);
			ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
			(as->column - (*line - as->temp)), DIRECT, ft_strndup(as->temp,
			(*line - as->temp))), sizeof(t_token)));
			as->count =
			(as->flags & DEBUG_L) ? ft_printf("--add DIRECT token\n") : 0;
		}
	}
	return (SUCCESS);
}

t_bool			skip_comment_line(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	while (**line != '\n')
		increment_line(as, line, 1);
	return (SUCCESS);
}

t_bool			skip_whitespaces(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	while ((**line == ' ' || **line == '\t' || **line == '\v' ||
	**line == '\f'))
		increment_line(as, line, 1);
	return (SUCCESS);
}

t_bool			process_line(t_project *as, char **line)
{
	size_t		index;

	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	index = 0;
	while (**line != '\n' && **line != '\0')
	{
		if (ft_strchr(g_look_up[index].chars, **line))
		{
			as->temp = *line;
			if (!(g_look_up[index].func(as, line)))
				return (FAIL);
			index = -1;
		}
		index++;
		if (index == (LOOK_UP_LEVELS))
			return (FAIL);
	}
	return (SUCCESS);
}

void			endline_token(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	ft_lstadd_back(&as->token_list,
	ft_lstnew_ptr((void*)new_token(as, as->column,
	ENDLINE, NULL), sizeof(t_token)));
	increment_line(as, line, 1);
	as->count = (as->flags & DEBUG_L) ? ft_printf("--add ENDLINE token\n") : 0;
	as->row++;
	as->column = 0;
}

void			end_token(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	ft_lstadd_back(&as->token_list,
	ft_lstnew_ptr((void*)new_token(as, as->column,
	END, NULL), sizeof(t_token)));
	as->count = (as->flags & DEBUG_L) ? ft_printf("--add END token\n") : 0;
}

t_token			*new_token(t_project *as, size_t y_axis, short type, char *str)
{
	t_token		*temp;

	temp = (t_token*)ft_memalloc(sizeof(t_token));
	if (!temp)
		return (NULL);
	temp->row = as->row;
	temp->column = y_axis;
	temp->literal_str = str;
	temp->token_type = type;
	return (temp);
}

t_bool			analyze_lexicon(t_project *as)
{
	char		*line;
	char		*temp;

	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	while (get_next_endline(as->fd, &line))
	{
		temp = line;
		if (!process_line(as, &temp))
		{
			ft_dprintf(2, LEXICAL_ERR, (as->row + 1), (as->column + 1));
			exit(0);
			return (FAIL);
		}
		if (*temp == '\n')
			endline_token(as, &temp);
		if (as->og_line != NULL)
		{
			free(as->og_line);
			as->og_line = NULL;
		}
		free(line);
		as->temp = NULL;
	}
	end_token(as);
	return (SUCCESS);
}
