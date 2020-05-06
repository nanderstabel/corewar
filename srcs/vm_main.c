#include "corewar.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl_fd("enter a number", 1);
		return (1);
	}
	some_vm_function(argv[1]);
	return (0);
}