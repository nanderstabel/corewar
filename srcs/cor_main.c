#include "corewar.h"
#include "op.h"
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

// int		main(int argc, char **argv)
// {
// 	t_vm	vm;

// 	ft_bzero(&vm, sizeof(t_vm));
// 	vm.dump = -1;
// 	if (argc == 1)
// 		return (print_message(USAGE, NULL, STDOUT, SUCCESS));
// 	if (input_validation(&vm, argv, argc) == ERROR)
// 		return (free_vm(&vm, ERROR));
// 	vm_start(&vm);
// 	return (free_vm(&vm, SUCCESS));
// }

int	main(int argc, char **argv)
{
	unsigned char arena[MEM_SIZE];

	arena[0] = 0;
	arena[1] = 1;
	arena[2] = 15;
	arena[3] = 255;

	ft_printf("	arena[0] = %d = 0x%s, arena[1] = %d = 0x%s, arena[2] = %d = 0x%s, arena[3] = %d = 0x%s\n", arena[0], ft_itoa_base_unsgnd((unsigned long long)arena[0], 16, 0, 1), arena[1], ft_itoa_base_unsgnd((unsigned long long)arena[1], 16, 0, 1), arena[2], ft_itoa_base_unsgnd((unsigned long long)arena[2], 16, 0, 1), arena[3], ft_itoa_base_unsgnd((unsigned long long)arena[3], 16, 0, 1));
	return (0);
}
