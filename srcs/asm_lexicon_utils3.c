/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_lexicon_utils3.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 15:20:01 by nstabel       #+#    #+#                 */
/*   Updated: 2020/08/07 15:21:55 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
