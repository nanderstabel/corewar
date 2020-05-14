/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_token_tab.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 16:40:21 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/14 20:23:47 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token_tab		token_tab[END + 1] = 
{
	{"INDIRECT_LABEL", IND_SIZE, translate_indirect_label,
		{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}},
	{"LABEL", 0, NULL, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}},
	{"INSTRUCTION", 1 ,translate_instruction,
		 {1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0}},
	{"REGISTER", 1, translate_register, 
		{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}},
	{"SEPARATOR", 0, NULL, {1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0}},
	{"DIRECT_LABEL", IND_SIZE, translate_direct_label,
		{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}},
	{"DIRECT", DIR_SIZE, translate_direct,
		{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}},
	{"COMMAND_NAME", 0, NULL, {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}},
	{"COMMAND_COMMENT", 0, NULL, {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}},
	{"STRING", 0, NULL, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}},
	{"ENDLINE", 0, NULL, {2, 1, 1, 2, 2, 2, 2, 1, 1, 0, 1, 0, 1}},
	{"INDIRECT", IND_SIZE, translate_indirect,
		{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}},
	{"END", 0, NULL, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
};
