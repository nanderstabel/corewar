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
		return (print_message(USAGE, NULL, STDOUT, SUCCESS));
	if (input_validation(&vm, argv, argc) == ERROR)
		return (free_vm(&vm, ERROR));
	vm_start(&vm);
	if (vm.cursors == NULL || vm.cursors->next == NULL)
		ft_printf("Contestant %d, \"%s\", has won !\n", vm.last_live, \
			vm.champ[vm.last_live]->header.prog_name);
	return (free_vm(&vm, SUCCESS));
}

// int	main(void)
// {
// 	unsigned char arena[MEM_SIZE];

// 	arena[0] = 0;
// 	arena[1] = 32;
// 	arena[2] = 31;
// 	arena[3] = 255;

// 	ft_printf("	arena[0] = %d = 0x%s\n arena[1] = %d = 0x%s\n arena[2] = %d = 0x%s\n arena[3] = %d = 0x%s\n", arena[0], cor_itoa(arena[0]), arena[1], cor_itoa(arena[1]), arena[2], cor_itoa(arena[2]), arena[3], cor_itoa(arena[3]));
// 	return (0);
// }
