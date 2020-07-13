/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_helpers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/10 14:51:50 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/13 17:04:54 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_arg_type(unsigned char enc, unsigned int no)
{
	char	type;

	type = (enc >> 6);
	if (no == 1)
		return (type);
	enc ^= (type << 6);
	type = (enc >> 4);
	if (no == 2)
		return (type);
	enc ^= (type << 4);
	type = (enc >> 2);
	if (no == 3)
		return (type);
	enc ^= (type << 2);
	type = (enc >> 2);
	if (no == 4)
		return (type);
	return (-1);
}

void	store_int_arena(unsigned char *arena, unsigned int idx, int value)
{
	arena[idx] = ((unsigned char*)&value)[3];
	arena[new_idx(idx, 1, FALSE)] = ((unsigned char*)&value)[2];
	arena[new_idx(idx, 2, FALSE)] = ((unsigned char*)&value)[1];
	arena[new_idx(idx, 3, FALSE)] = ((unsigned char*)&value)[0];
}
