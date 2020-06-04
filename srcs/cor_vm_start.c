/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_vm_start.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 11:22:16 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/06/03 11:22:16 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	cursors_init(t_vm *vm)
{
	unsigned int	idx;
	t_cursor		*new_cursor;

	idx = 1;
	ft_printf("Introducing contestants...\n");
	while (idx <= vm->champ_count)
	{
		ft_printf("Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", idx, \
		vm->champ[idx]->header.prog_size, vm->champ[idx]->header.prog_name, \
		vm->champ[idx]->header.comment);
		new_cursor = (t_cursor*)ft_memalloc(sizeof(t_cursor));
		if (new_cursor == NULL)
			return (ERROR);
		new_cursor->pc = (MEM_SIZE / vm->champ_count) * idx;
		// ft_strcpy(&(vm->arena[new_cursor->pc]), vm->champ[idx]->exec_code);
		new_cursor->reg[1] = -idx;
		new_cursor->next = vm->cursors;
		vm->cursors = new_cursor;
		// new_cursor->color = 'player color';
		// call visualizer with champ color and prog_size
		++idx;
	}
	return (SUCCESS);
}

int			vm_start(t_vm *vm)
{
	if (cursors_init(vm) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
