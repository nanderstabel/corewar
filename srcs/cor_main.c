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
	vm.dump = -1;
	if (argc == 1)
		return (print_message(USAGE, NULL, STDOUT, SUCCESS));
	if (input_validation(&vm, argv, argc) == ERROR)
		return (free_vm(&vm, ERROR));
	vm_start(&vm);
	return (free_vm(&vm, SUCCESS));
}
