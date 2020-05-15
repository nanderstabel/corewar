/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_is_argument.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 00:47:38 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/15 00:47:59 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool			is_argument(char token)
{
	if (token == INDIRECT_LABEL || token == REGISTER || token == DIRECT_LABEL \
		|| token == DIRECT || token == INDIRECT)
		return (SUCCESS);
	return (FAIL);
}
