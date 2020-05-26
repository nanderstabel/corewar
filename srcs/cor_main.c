#include "corewar.h"
#include "op.h"
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

// int		ft_cor_read(char *file)
// {
// 	char *buf;
// 	char magic[4];
// 	int fd;
// 	int max_size;
// 	int curr_offset;

// 	max_size = (PROG_NAME_LENGTH < COMMENT_LENGTH) ? COMMENT_LENGTH : PROG_NAME_LENGTH;
// 	max_size = (CHAMP_MAX_SIZE < COMMENT_LENGTH) ? COMMENT_LENGTH : CHAMP_MAX_SIZE;
// 	fd = open(file, O_RDONLY);
// 	if (fd == -1)
// 		return (-1);
// 	buf = ft_memalloc(sizeof(char *) * max_size + 1);
// 	curr_offset = lseek(fd, 0, SEEK_SET);
// 	ft_printf("offset = %d\n", curr_offset);
// 	read(fd, magic, 4);
// 	ft_strrev(magic);
// 	ft_printf("%x\n", (int)buf);
// 	return (0);
// }

int		main(int argc, char **argv)
{
	t_vm	vm;

	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	if (argc == 1)
		return (print_message(0, NULL, STDOUT, SUCCESS));
	if (input_validation(&vm, argv, argc) == ERROR)
		return (free_vm(&vm, ERROR));
	ft_putendl("input is valid");
	return (free_vm(&vm, SUCCESS));
}
