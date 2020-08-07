/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_lexicon_utils4.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 15:15:02 by nstabel       #+#    #+#                 */
/*   Updated: 2020/08/07 15:22:15 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
