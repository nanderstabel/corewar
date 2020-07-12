/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_vm_helpers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/28 17:10:22 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/10 16:45:04 by lhageman      ########   odam.nl         */
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

int				convert_to_int(unsigned char *start, unsigned int len)
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

void			put_exec_code(unsigned char *code, unsigned int size)
{
	unsigned int	idx;

	idx = 0;
	while (idx < size)
	{
		if (idx == 0 || (idx + 1) % 64 != 0)
			ft_printf("%s ", vis_itoa(code[idx]));
		else
			ft_printf("%s\n", vis_itoa(code[idx]));
		idx += 1;
	}
	if ((idx + 1) % 64 != 0)
		write(1, "\n", 1);
}

void			put_arena(unsigned char *arena)
{
	unsigned int	idx;

	idx = 0;
	while (idx < MEM_SIZE)
	{
		if (idx == 0 || (idx + 1) % 64 != 0)
			ft_printf("%s ", vis_itoa(arena[idx]));
		else
			ft_printf("%s\n", vis_itoa(arena[idx]));
		idx += 1;
	}
}
