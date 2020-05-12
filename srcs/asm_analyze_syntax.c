/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_analyze_syntax.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/12 17:20:37 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_token		*temp_test(void)
{
	t_token		*list;

	list = ft_memalloc(sizeof(t_token));
	list->token_type = COMMAND_NAME;
	list->next = ft_memalloc(sizeof(t_token));
	list->next->token_type = STRING;
	list->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->token_type = ENDLINE;
	list->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->token_type = COMMAND_COMMENT;
	list->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->token_type = STRING;
	list->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->token_type = ENDLINE;
	list->next->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->next->token_type = LABEL;
	list->next->next->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->next->next->token_type = ENDLINE;
	list->next->next->next->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->next->next->next->token_type = INSTRUCTION;
	list->next->next->next->next->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->next->next->next->next->token_type = REGISTER;
	list->next->next->next->next->next->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->next->next->next->next->next->token_type = INSTRUCTION; //SEPARATOR;
	list->next->next->next->next->next->next->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->next->next->next->next->next->next->token_type = DIRECT;
	list->next->next->next->next->next->next->next->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->next->next->next->next->next->next->next->token_type = SEPARATOR;
	list->next->next->next->next->next->next->next->next->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->next->next->next->next->next->next->next->next->token_type = DIRECT_LABEL;
	list->next->next->next->next->next->next->next->next->next->next->next->next->next->next = ft_memalloc(sizeof(t_token));
	list->next->next->next->next->next->next->next->next->next->next->next->next->next->next->token_type = ENDLINE;
	list->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = NULL;
	return (list);
}

t_bool			analyze_syntax(t_project *as)
{
	t_token		*list;

	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	if (as->flags & DEBUG_O)
	{
		ft_putchar(10);
		list = temp_test();
		while (list->next)
		{
			if (token_tab[list->token_type].next[list->next->token_type])
				ft_printf("\t%s --> %s\n", token_tab[list->token_type].string, token_tab[list->next->token_type].string);
			else
			{
				ft_printf("\tSyntax error at token [TOKEN][000:000] %s \"\"\n", token_tab[list->next->token_type].string);
				break;
			}
			list = list->next;
		}
		ft_putchar(10);
	}
	return (SUCCESS);	
}

