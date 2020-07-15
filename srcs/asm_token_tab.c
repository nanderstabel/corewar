/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_token_tab.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 16:40:21 by nstabel       #+#    #+#                 */
/*   Updated: 2020/07/09 18:33:25 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token_tab		g_token_tab[END + 1] =
{
	{"INDIRECT_LABEL", "indirect", IND_SIZE, IND_CODE, translate_label,
		{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}},
	{"LABEL", NULL, 0, 0, NULL, {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}},
	{"INSTRUCTION", NULL, 1, 0, translate_instruction,
		{1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0}},
	{"REGISTER", "register", 1, REG_CODE, translate_argument,
		{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}},
	{"SEPARATOR", NULL, 0, 0, NULL, {1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0}},
	{"DIRECT_LABEL", "direct", DIR_SIZE, DIR_CODE, translate_label,
		{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}},
	{"DIRECT", "direct", DIR_SIZE, DIR_CODE, translate_argument,
		{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}},
	{"COMMAND_NAME", NULL, 0, 0, NULL, {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}},
	{"COMMAND_COMMENT", NULL, 0, 0, NULL,
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}},
	{"STRING", NULL, 0, 0, NULL, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}},
	{"ENDLINE", NULL, 0, 0, NULL, {0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1}},
	{"INDIRECT", "indirect", IND_SIZE, IND_CODE, translate_argument,
		{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}},
	{"END", NULL, 0, 0, NULL, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
};
