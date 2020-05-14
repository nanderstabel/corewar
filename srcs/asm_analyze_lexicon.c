/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_analyze_lexicon.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/14 10:54:35 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_redirect	look_up[] = 
{
	{" \t\v\f", skip_whitespaces},
	{"#;", skip_comment_line},
	{".", command_token},
	{"%", direct_token},
	{":", indirect_label_token},
	{LABEL_CHARS, label_token}
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
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	(void)line;
	return (SUCCESS);
}

t_bool			label_token(t_project *as, char **line)
{
	int			index;

	index = 0;
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	if (**line == 'r')
	{
		while (index < 2 && (**line))
		{
			if (!ft_isdigit((int)(*line)[index]))
				break ;
			index++;
		}
		if (index == 2 && *((*line) + index) != ':') // Deze ------------
		{
			ft_printf("into register\n");
			if (!register_token(as, line))
				return (FAIL);
		}
	}
	else if (!is_valid_label_chars(as, line))
	{
		ft_printf("is valid chars failed\n");
		if (*((*line) - 1) == ':')
			ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
			(as->column - (*line - as->temp)), LABEL, ft_strndup(as->temp,
			(*line - as->temp))), sizeof(t_token)));
		else
			return (FAIL);
	}
	else
	{
		ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as,
		(as->column - (*line - as->temp)), LABEL, ft_strndup(as->temp,
		(*line - as->temp))), sizeof(t_token)));
	}
	
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
	// ft_printf("char3 %c\n", **line);
	return (SUCCESS);
}

t_bool			indirect_label_token(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	increment_line(as, line, 1);
	if (ft_strchr(LABEL_CHARS, **line))
	{
		if (!is_valid_label_chars(as, line))
		{
			// ft_printf("char1 %c\n", **line);
			return (FAIL);
		}
		ft_lstadd_back(&as->token_list, ft_lstnew_ptr(
			(void*)new_token(as, (as->column - (*line - as->temp)), INDIRECT_LABEL, ft_strndup(as->temp,(*line - as->temp))), sizeof(t_token)));		
		return (SUCCESS);
	}
	// ft_printf("char2 %c\n", **line);
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
	{
		as->column++;
		(*line)++;
	}
	return (SUCCESS);
}

t_bool			skip_whitespaces(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	while ((**line == ' ' || **line == '\t' || **line == '\v' ||
	**line == '\f') && (**line != '\0'))
	{
		as->column++;
		(*line)++;
	}
	return (SUCCESS);
}

t_bool				process_line(t_project *as, char **line)
{

	int		index;

	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;

	index = 0;
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

// void			process_line(t_project *as, char **line)
// {
// 	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
// 	while (**line)
// 	{
// 		if (**line == ' ' || **line == '\t' || **line == '\v' || **line == '\f')
// 			skip_whitespaces(as, line);
// 		else if (**line == COMMENT_CHAR || **line == ';')
// 			;//skip comment
// 		else if (**line == DIRECT_CHAR)
// 			;//indirect or indirect label
// 		else if (**line == 'r')
// 			;//registry or label
// 		else if (**line == LABEL_CHAR)
// 			;//indirect label
// 		else if (**line == '-' || ft_isdigit((int)(**line)))
// 			;//direct
// 		else if (ft_strchr(LABEL_CHARS, **line))
// 			;//label or instruction
// 		else if (**line == SEPARATOR_CHAR)
// 			;//separator
// 		else if (**line == '\n')
// 			;//ENDLINE token
// 		else if (**line == '"')
// 			;//string
// 		else
// 		{
// 			;//ERROR
// 		}
// 	}
	
// }

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
	while (get_next_line(as->fd, &line))
	{
		as->row++;
		temp = line;
		if (!process_line(as, &temp))
		{
			ft_printf(LEXICAL_ERR, as->row, (as->column - 1));
			return (FAIL);
		}
		ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as, as->column, ENDLINE, NULL), sizeof(t_token)));
	}
	ft_lstadd(&as->token_list, ft_lstnew_ptr((void*)new_token(as, as->column, END, NULL), sizeof(t_token)));
	
	return (SUCCESS);	
}
