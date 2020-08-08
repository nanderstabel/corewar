/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_analyze_lexicon.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/08/07 15:22:11 by nstabel       ########   odam.nl         */
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
