/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_analyze_lexicon.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/14 09:51:15 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_redirect	look_up[] = 
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

t_bool			command_token(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	if (ft_wspace_strequ(*line, ".name"))
	{
		as->column += 5;
		ft_lstadd_back(&as->token_list,
		ft_lstnew_ptr((void*)new_token(as, as->column,
		COMMAND_NAME, ".name"), sizeof(t_token)));
	}
	else if (ft_wspace_strequ(*line, ".comment"))
	{
		as->column += 8;
		ft_lstadd_back(&as->token_list,
		ft_lstnew_ptr((void*)new_token(as, as->column,
		COMMAND_COMMENT, ".comment"), sizeof(t_token)));
	}
	else
		return (FAIL);
	return (SUCCESS);
}

t_bool			register_token(t_project *as, char **line)
{
	int		increment;

	increment = 1;
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	increment_line(as, line, 1);
	if ((**line == '0' && ft_strchr(END_LABEL_CHARS,*((*line) + 1))) ||
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
	return (SUCCESS);
}

t_bool			label_instruction_token(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	if (!is_valid_label_chars(as, line))
	{
		if (**line == ':')
		{
			increment_line(as, line, 1);
			ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
			(as->column - (*line - as->temp)), LABEL, ft_strndup(as->temp,
			(*line - as->temp))), sizeof(t_token)));
		}
		else
			return (FAIL);
	}
	else
	{
		ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
		(as->column - (*line - as->temp)), INSTRUCTION, ft_strndup(as->temp,
		(*line - as->temp))), sizeof(t_token)));
	}
	return (SUCCESS);
}


t_bool			string_token(t_project *as, char **line)
{
	char		*temp_str;
	char		*delete;
	t_list		*temp_list;
	int			len;

	len = 0;
	delete = NULL;
	temp_list = as->token_list;
	if (as->index)
	{
		temp_list = ft_list_last_elem(as->token_list);
		delete = ((t_token*)temp_list->content)->literal_str;
	}
	if (!as->index)
		increment_line(as, line, 1);
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	temp_str = ft_strchr(*line, (int)'"');
	if (!temp_str)
	{
		if (as->index)
		{
			// delete = ((t_token*)temp_list->content)->literal_str;
			((t_token*)temp_list->content)->literal_str = ft_strjoin(delete, *line);
			free(delete);
		}
		else
		{
			ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
			(as->column - (*line - as->temp)), STRING, ft_strdup(as->temp)), sizeof(t_token)));
		}
		increment_line(as, line, ft_strlen(*line) - 1);
		as->index = 1;
	}
	else
	{
		len =  temp_str - as->temp;
		if (as->index)
		{
			// ft_printf("len - %d\nas->temp - %s\nchar - %c\n", len, as->temp, as->temp[len]);
			// delete = ((t_token*)temp_list->content)->literal_str;
			temp_str = ft_strndup(as->temp, len + 1);
			// ft_printf("string in list - %s\nstr to join - %s\n", delete, temp_str);
			((t_token*)temp_list->content)->literal_str = ft_strjoin(delete, temp_str);
			free(delete);
			free(temp_str);
			as->index = 0;
			// increment_line(as, line, len);

		}
		else
		{
			// ft_printf("new token\n");
			ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
			(as->column - (*line - as->temp)), STRING, ft_strndup(as->temp, len + 1)), sizeof(t_token)));
		}
		increment_line(as, line, len);
		// ft_printf("print char line %c\n", *((*line) - 1));
	}
	// "sdkfjsdk"F
	return (SUCCESS);
}

t_bool			separator_token(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
	(as->column - (*line - as->temp)), SEPARATOR, ft_strndup(as->temp,
	(*line - as->temp))), sizeof(t_token)));
	increment_line(as, line, 1);
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
		if (index + 1 <= TWO_DIGITS && *((*line) + index + 1) != ':' &&
		ft_strchr(END_LABEL_CHARS, *((*line) + index + 1)) &&
		!ft_strchr(LABEL_CHARS, *((*line) + index + 1)))
		{
			if (!register_token(as, line))
				return (FAIL);
			return (SUCCESS);
		}
	}
	while (ft_isdigit((int)(*line)[index]))
		index++;
	if (index > 0 && ft_strchr(END_LABEL_CHARS, *((*line) + index)))
	{
		indrect_token(as, line);
		return (SUCCESS);
	}
	if (!label_instruction_token(as, line))
		return (FAIL);
	return (SUCCESS);
}

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
			INDIRECT_LABEL,
			ft_strndup(as->temp,(*line - as->temp))), sizeof(t_token)));		
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
	return (SUCCESS);
}

void			increment_line(t_project *as, char **line, size_t len)
{
	size_t index;

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
		}
	}
	return (SUCCESS);
}

t_bool			skip_comment_line(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	while (**line)
		increment_line(as, line, 1);
	return (SUCCESS);
}

t_bool			skip_whitespaces(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	while ((**line == ' ' || **line == '\t' || **line == '\v' ||
	**line == '\f') && (**line != '\0'))
		increment_line(as, line, 1);
	return (SUCCESS);
}

t_bool				process_line(t_project *as, char **line)
{

	int		index;

	index = 0;
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	while (**line)
	{
		if (ft_strchr(look_up[index].chars, **line))
		{
			as->temp = *line;
			if (!(look_up[index].func(as, line)))
				return (FAIL);
			index = 0;
		}
		index++;
	}
	as->column++;
	return (SUCCESS);

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

	return (SUCCESS);	//Delete this
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	while (get_next_line(as->fd, &line))
	{
		as->row++;
		temp = line;
		if (as->index)
			string_token(as, &temp);
		if (!process_line(as, &temp))
		{
			ft_printf(LEXICAL_ERR, as->row, (as->column - 1));
			return (FAIL);
		}
		ft_lstadd_back(&as->token_list,
		ft_lstnew_ptr((void*)new_token(as, as->column,
		ENDLINE, NULL), sizeof(t_token)));
	}
	ft_lstadd(&as->token_list,
	ft_lstnew_ptr((void*)new_token(as, as->column,
	END, NULL), sizeof(t_token)));
	return (SUCCESS);	
}
