/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_analyze_lexicon.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/15 22:31:12 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_redirect		look_up[] =
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
** The function checks if the first part of the string (until whitespaces) is
** a valid COMMAND token. If so a link is added to the link list. If not
** it is a lexical error.
**
** t_project 	*as			struct of type t_project. Holds all data for the asm
** char			**line		points current place in the line
**
** return (SUCCESS)			element is added to the list as->token_list
** return (FAIL)			lexical error is found
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
** The function checks if it's a valid REGISTER token. If so a link is added to
** the link list. If not it is a lexical error.
**
** t_project 	*as			struct of type t_project. Holds all data for the asm
** char			**line		points current place in the line
**
** return (SUCCESS)			element is added to the list as->token_list
** return (FAIL)			lexical error is found
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
** The function loops through *line END_LABEL_CHARS are found. If so the string
** is valid. If there is a non LABEL_CHARS in the string it is not valid and
** so alexical error.
**
** t_project 	*as			struct of type t_project. Holds all data for the asm
** char			**line		points current place in the line
**
** return (SUCCESS)			string is valid
** return (FAIL)			lexical error is found
*/

t_bool			is_valid_label_chars(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	while (!ft_strchr(END_LABEL_CHARS, **line) && (**line))
	{
		if (!ft_strchr(LABEL_CHARS, **line))
			return (FAIL);
		increment_line(as, line, 1);
	}
	return (SUCCESS);
}

void			instruction_token(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	as->count =
	(as->flags & DEBUG_L) ? ft_printf("--add INSTRUCTION token\n") : 0;
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
	(as->column - (*line - as->temp)), INSTRUCTION, ft_strndup(as->temp,
	(*line - as->temp))), sizeof(t_token)));
}



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
** label_token checks if all chars are valid_label_chars. If not and the char it
** lands on is ':', it means it's a label. Otherwise it's a lexical error.
** a valid COMMAND token. If so a link is added to the link list. If not
** it is a lexical error.
**
** t_project 	*as			struct of type t_project. Holds all data for the asm
** char			**line		points current place in the line
**
** return (SUCCESS)			element is added to the list as->token_list
** return (FAIL)			lexical error is found
*/

t_bool			label_or_instruction_token(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	if (!is_valid_label_chars(as, line))
	{
		if (**line == ':')
		{
			label_token(as, line);
			// increment_line(as, line, 1);
			// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
			// (as->column - (*line - as->temp)), LABEL, ft_strndup(as->temp,
			// (*line - as->temp))), sizeof(t_token)));
			// as->count =
			// (as->flags & DEBUG_L) ? ft_printf("--add LABEL token\n") : 0;
		}
		else
			return (FAIL);
	}
	else
	{
		instruction_token(as, line);
		// as->count =
		// (as->flags & DEBUG_L) ? ft_printf("--add INSTRUCTION token\n") : 0;
		// ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
		// (as->column - (*line - as->temp)), INSTRUCTION, ft_strndup(as->temp,
		// (*line - as->temp))), sizeof(t_token)));
	}
	return (SUCCESS);
}

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

int				add_to_string_token(t_project *as, char **line)
{
	char		*old_str;
	t_list		*l_temp;
	char		*temp;
	int			len;

	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	l_temp = ft_list_last_elem(as->token_list);
	old_str = ((t_token*)l_temp->content)->literal_str;
	temp = ft_strchr(*line, (int)'"');
	len = (temp - as->temp);
	if (!temp)
		((t_token*)l_temp->content)->literal_str = ft_strjoin(old_str, *line);
	else
	{
		temp = ft_strndup(as->temp, len + 1);
		((t_token*)l_temp->content)->literal_str = ft_strjoin(old_str, temp);
		free(temp);
	}
	as->count = (as->flags & DEBUG_L) ? ft_printf("--add STRING token\n") : 0;
	free(old_str);
	if (!temp)
		return (0);
	return (len);
}

int				new_string_token(t_project *as, char **line)
{
	char		*str_temp;
	int			len;

	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	increment_line(as, line, 1);
	str_temp = ft_strchr(*line, (int)'"');
	len = str_temp - as->temp;
	if (!str_temp)
	{
		ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
		(as->column - (*line - as->temp)), STRING, ft_strdup(as->temp)),
		sizeof(t_token)));
		as->count =
		(as->flags & DEBUG_L) ? ft_printf("--add STRING token\n") : 0;
		return (0);
	}
	else
	{
		ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
		(as->column - (*line - as->temp)), STRING, ft_strndup(as->temp,
		len + 1)), sizeof(t_token)));
		as->count =
		(as->flags & DEBUG_L) ? ft_printf("--add STRING token\n") : 0;
		return (len);
	}
}

t_bool			string_token(t_project *as, char **line)
{
	int			ret;

	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	if (as->index)
		ret = add_to_string_token(as, line);
	else
		ret = new_string_token(as, line);
	if (ret)
	{
		as->index = 0;
		increment_line(as, line, ret);
	}
	else
	{
		increment_line(as, line, ft_strlen(*line) - 1);
		as->index = 1;
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
	**line == '\f'))// && (**line != '\0')
		increment_line(as, line, 1);
	return (SUCCESS);
}

t_bool			process_line(t_project *as, char **line)
{
	size_t			index;

	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	index = 0;
	while (**line != '\n' && **line != '\0')
	{
		// if (**line == '\0')
		// 	return (SUCCESS);
		if (ft_strchr(look_up[index].chars, **line))
		{
			as->temp = *line;
			if (!(look_up[index].func(as, line)))
				return (FAIL);
			index = -1;
		}
		index++;
		if (index == (LOOK_UP_LEVELS))
			return (FAIL);
		// ft_printf("char in process line [%c]\n", **line);
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
		if (as->index)
			string_token(as, &temp);
		if (!process_line(as, &temp))
		{
			ft_printf(LEXICAL_ERR, (as->row + 1), (as->column + 1));
			//wis link list
			return (FAIL);
		}
		// ft_printf("char line after provess line [%c]\n", *temp);
		if (*temp == '\n')
		{
			endline_token(as, &temp);
			as->row++;
			as->column = 0;

		}
		free(line);
		as->temp = NULL;
	}
	end_token(as);
	return (SUCCESS);
}
