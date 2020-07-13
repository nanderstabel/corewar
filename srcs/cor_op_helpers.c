/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_op_helpers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/10 14:51:50 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/13 12:02:32 by lhageman      ########   odam.nl         */
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
