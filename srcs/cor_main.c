#include "corewar.h"
#include "op.h"
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

char *ft_strrev(char *str)
{
	char *new;
	int i;
	int j;

	new = ft_memalloc(ft_strlen(str) + 1);
	i = ft_strlen(str);
	j = 0;
	while (i >= 0)
	{
		new[j] = str[i];
		j += 1;
		i -= 1;
	}
	return (new);
}

int	ft_cor_read(char *file)
{
	char *buf;
	char magic[4];
	char *rev;
	int fd;
	int max_size;
	int curr_offset;

	max_size = (PROG_NAME_LENGTH < COMMENT_LENGTH) ? COMMENT_LENGTH : PROG_NAME_LENGTH;
	max_size = (CHAMP_MAX_SIZE < COMMENT_LENGTH) ? COMMENT_LENGTH : CHAMP_MAX_SIZE;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	buf = ft_memalloc(sizeof(char *)* max_size + 1);
	curr_offset = lseek(fd, 0, SEEK_SET);
	ft_printf("offset = %d\n", curr_offset);
	read(fd, magic, 4);
	rev = ft_strrev(magic);
	ft_printf("%x\n", (int)buf);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl_fd("Give one file", 1);
		return (1);
	}
	ft_cor_read(argv[1]);
	return (0);
}