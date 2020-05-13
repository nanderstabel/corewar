/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_analyze_lexicon.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/12 21:26:10 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_redirect	look_up[] = 
{
	{" \t\v\f", skip_whitespaces},
	{"#;", skip_comment_line},
	{".", command_token},
	{"%", direct_token}
};

t_bool			command_token(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	if (ft_wspace_strequ(*line, ".name"))
	{
		as->column += 5;
		ft_lstadd_back(&as->token_list,
		ft_lstnew_ptr((void*)new_token(as,
		COMMAND_NAME, ".name"), sizeof(t_token)));
	}
	else if (ft_wspace_strequ(*line, ".comment"))
	{
		as->column += 8;
		ft_lstadd_back(&as->token_list,
		ft_lstnew_ptr((void*)new_token(as,
		COMMAND_COMMENT, ".comment"), sizeof(t_token)));
	}
	else
		return (FAIL);
	return (SUCCESS);
}

t_bool			direct_label_token(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	(void)line;
	return (SUCCESS);

}

t_bool			direct_token(t_project *as, char **line)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	ft_printf("test\n");
	if (*(*line + 1) == ':')
	{
		if (!direct_label_token(as, line))
		return (FAIL);
	}
	else
	{
		/* code */
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
			if (!(look_up[index].func(as, line)))
				return (FAIL);
			index = 0;
		}
		index++;
		if (**line == 't')
			break ;
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

t_token			*new_token(t_project *as, short type, char *str)
{
	t_token		*temp;

	temp = (t_token*)ft_memalloc(sizeof(t_token));
	if (!temp)
		return (NULL);
	temp->row = as->row;
	temp->column = as->column;
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
		if (!process_line(as, &temp))
		{
			//print error
			return (FAIL);
		}
		ft_lstadd_back(&as->token_list, ft_lstnew_ptr((void*)new_token(as, ENDLINE, NULL), sizeof(t_token)));
	}
	ft_lstadd(&as->token_list, ft_lstnew_ptr((void*)new_token(as, END, NULL), sizeof(t_token)));
	
	return (SUCCESS);	
}
