/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_vm_helpers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/28 17:10:22 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/21 18:35:39 by lhageman      ########   odam.nl         */
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

int				convert_to_int(unsigned char *arena, unsigned int idx, \
				unsigned int len)
{
	int				value;
	unsigned int	i;
	char			sign;

	sign = arena[idx] >> 7;
	value = sign ? ~0 : 0;
	i = len;
	while (i > 0)
	{
		((unsigned char*)&value)[len - i] = arena[new_idx(idx, i - 1, FALSE)];
		--i;
	}
	return (value);
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
	ft_putstr("0x0000 : ");
	while (idx < MEM_SIZE)
	{
		if (idx != 0 && idx % 64 == 0)
			ft_printf("%#06x : ", idx);
		ft_printf("%s ", vis_itoa(arena[idx]));
		if ((idx + 1) % 64 == 0)
			ft_printf("\n", vis_itoa(arena[idx]));
		idx += 1;
	}
}
