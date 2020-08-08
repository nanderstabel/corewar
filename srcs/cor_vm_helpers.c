/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_vm_helpers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/28 17:10:22 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/08/08 11:54:27 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			print_pc(t_vm *vm, t_cursor *cursor, size_t size)
{
	int c;

	if (vm->vis == NULL)
		return ;
	vm->vis->bytes = 1;
	c = 0;
	if (size > 0)
	{
		vm->vis->index = new_idx(cursor->pc, -size, TRUE);
		c = vis_calc_inch(vm);
		vm->vis->attr[cursor->player](vis_calc_att(FALSE, TRUE), \
		vm->vis->graphics->arena);
		vis_print_cursor(vm->vis);
		usleep(10000);
		wattron(vm->vis->graphics->arena, COLOR_PAIR(c));
		wattroff(vm->vis->graphics->arena, A_BOLD);
		vis_print_cursor(vm->vis);
		usleep(5000);
	}
}

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
	char			*hex;

	idx = 0;
	ft_putstr("0x0000 : ");
	while (idx < MEM_SIZE)
	{
		hex = vis_itoa(arena[idx]);
		if (idx != 0 && idx % 64 == 0)
			ft_printf("%#06x : ", idx);
		ft_printf("%s ", hex);
		if ((idx + 1) % 64 == 0)
			ft_printf("\n", hex);
		ft_strdel(&hex);
		idx += 1;
	}
}
