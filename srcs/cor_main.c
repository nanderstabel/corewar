/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_main.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/25 12:46:51 by nstabel       #+#    #+#                 */
/*   Updated: 2020/08/08 10:48:07 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int		main(int argc, char **argv)
{
	t_vm	vm;

	ft_bzero(&vm, sizeof(t_vm));
	ft_bzero(vm.arena, MEM_SIZE);
	vm.dump = -1;
	if (argc == 1)
		return (print_usage(0));
	if (input_validation(&vm, argv, argc) == ERROR)
		return (free_vm(&vm));
	vm_start(&vm);
	if (vm.cursors != NULL && \
		vm.dump >= 0 && (unsigned int)vm.dump == vm.total_cycle_count)
		put_arena(vm.arena);
	else
		ft_printf("Contestant %d, \"%s\", has won !\n", vm.last_live, \
			vm.champ[vm.last_live]->header.prog_name);
	return (free_vm(&vm));
}
