/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_token_tab.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 16:40:21 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/12 16:51:21 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token_tab		token_tab[END + 1] = 
{
	[INDIRECT_LABEL] = {"INDIRECT_LABEL" , {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}},
	[LABEL] = {"LABEL" , {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}},
	[INSTRUCTION] = {"INSTRUCTION" , {1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0}},
	[REGISTER] = {"REGISTER" , {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}},
	[SEPARATOR] = {"SEPARATOR" , {1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0}},
	[DIRECT_LABEL] = {"DIRECT_LABEL" , {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}},
	[DIRECT] = {"DIRECT" , {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}},
	[COMMAND_NAME] = {"COMMAND_NAME" , {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}},
	[COMMAND_COMMENT] = {"COMMAND_COMMENT" , {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}},
	[STRING] = {"STRING" , {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}},
	[ENDLINE] = {"ENDLINE" , {2, 1, 1, 2, 2, 2, 2, 1, 1, 0, 1, 0, 1}},
	[INDIRECT] = {"INDIRECT" , {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}},
	[END] = {"END", {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
};
