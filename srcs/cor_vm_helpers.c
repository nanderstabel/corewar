/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_vm_helpers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/28 17:10:22 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/06 15:05:43 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int	new_idx(unsigned int current_idx, int offset,
				unsigned int l_flag)
{
	unsigned int	new_idx;

	offset = offset % MEM_SIZE;
	if (l_flag == FALSE)
		offset = offset % IDX_MOD;
	if (offset < 0 && (unsigned int)((-1) * offset) >= current_idx)
		new_idx = (MEM_SIZE + current_idx + offset) % MEM_SIZE;
	else
		new_idx = (current_idx + offset) % MEM_SIZE;
	return (new_idx);
}

void		kill_cursor(t_vm *vm, t_cursor *cursor)
{
	t_cursor	*walk;

	if (vm->cursors == cursor)
		vm->cursors = cursor->next;
	walk = vm->cursors;
	while (walk != NULL)
	{
		if (walk->next == cursor)
			walk->next = cursor->next;
		walk = walk->next;
	}
	// play killing sound
	return (cursor_del(cursor));
}

int			convert_to_int(unsigned char *start, unsigned int len)
{
	int		integer;

	integer = 0;
	if (len == 4)
		((unsigned char*)&integer)[len - 4] = start[3];
	if (len >= 3)
		((unsigned char*)&integer)[len - 3] = start[2];
	if (len >= 2)
		((unsigned char*)&integer)[len - 2] = start[1];
	if (len >= 1)
		((unsigned char*)&integer)[len - 1] = start[0];
	return (integer);
}