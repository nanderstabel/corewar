/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_analyze_syntax.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/12 16:14:45 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

typedef struct			s_token
{
	struct s_token		*next;
	int					type;
}						t_token;

int		seq_tab[END + 1][END + 1] = 
{
	[INDIRECT_LABEL] = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
	[LABEL] = {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	[INSTRUCTION] = {1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0},
	[REGISTER] = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
	[SEPARATOR] = {1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0},
	[DIRECT_LABEL] = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
	[DIRECT] = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
	[COMMAND_NAME] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	[COMMAND_COMMENT] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	[STRING] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	[ENDLINE] = {2, 1, 1, 2, 2, 2, 2, 1, 1, 0, 1, 0, 1},
	[INDIRECT] = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
	[END] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}	
};

static t_token		*temp_test(void)
{
	t_token		*list;

	list = ft_memalloc(sizeof(t_token));
	list->type = COMMAND_NAME;
	list->next = ft_memalloc(sizeof(t_token));
	list->next->type = STRING;
	list->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->type = ENDLINE;
	list->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->type = COMMAND_COMMENT;
	list->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->type = STRING;
	list->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->type = ENDLINE;
	list->next->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->next->type = LABEL;
	list->next->next->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->next->next->type = ENDLINE;
	list->next->next->next->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->next->next->next->type = INSTRUCTION;
	list->next->next->next->next->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->next->next->next->next->type = REGISTER;
	list->next->next->next->next->next->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->next->next->next->next->next->type = SEPARATOR;
	list->next->next->next->next->next->next->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->next->next->next->next->next->next->type = DIRECT;
	list->next->next->next->next->next->next->next->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->next->next->next->next->next->next->next->type = SEPARATOR;
	list->next->next->next->next->next->next->next->next->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->next->next->next->next->next->next->next->next->type = DIRECT_LABEL;
	list->next->next->next->next->next->next->next->next->next->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type = ENDLINE;
	list->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = NULL;
	return (list);
}

t_bool			analyze_syntax(t_project *as)
{
	t_token		*list;

	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	list = temp_test();
	while (list->next)
	{
		if (seq_tab[list->type][list->next->type])
			ft_printf("%i --> %i\n", list->type, list->next->type);
		else
			ft_printf("ERROR\n");
		list = list->next;
	}
	//op_tab;
	return (SUCCESS);	
}

