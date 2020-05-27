/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_input_file.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/22 16:46:37 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/05/22 16:46:37 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>
#include <unistd.h>

int			read_champion(char *buf, char *file_name, \
			unsigned int champ_file_size)
{
	int				fd;
	unsigned int	bytes_read;

	fd = open(file_name, O_RDONLY);
	if (fd == -1 || read(fd, buf, 0) == -1)
		return (print_message(FILE_NOT_EXIST, file_name, STDERR, ERROR));
	bytes_read = read(fd, buf, champ_file_size + 1);
	if (bytes_read > champ_file_size)
		return (print_message(FILE_TOO_BIG, file_name, STDERR, ERROR));
	if (bytes_read < champ_file_size - CHAMP_MAX_SIZE)
		return (print_message(FILE_TOO_SMALL, file_name, STDERR, ERROR));
	close(fd);
	return (bytes_read);
}

static int	check_for_null_bytes(char *buf)
{
	unsigned int	count;
	unsigned int	position_1;
	unsigned int	position_2;

	position_1 = 4 + PROG_NAME_LENGTH - 1;
	position_2 = position_1 + 4 + COMMENT_LENGTH;
	count = 0;
	while (count < 4)
	{
		if (buf[position_1] != '\0' || buf[position_2] != '\0')
			return (ERROR);
		++count;
	}
	return (SUCCESS);
}

int			convert_to_int(char *start)
{
	int		integer;

	integer = 0;
	((char*)&integer)[0] = (unsigned char)start[3];
	((char*)&integer)[1] = (unsigned char)start[2];
	((char*)&integer)[2] = (unsigned char)start[1];
	((char*)&integer)[3] = (unsigned char)start[0];
	return (integer);
}

static int	check_for_cor_extension(char *file_name)
{
	int		count;

	count = 0;
	if (file_name[0] == '.' && file_name[0] != '\0' && file_name[1] == '/')
		count += 2;
	while (file_name[count] == '.' && file_name[count] != '\0' && \
		file_name[count + 1] == '.' && file_name[count + 1] != '\0' && \
		file_name[count + 2] == '/')
		count += 3;
	if (ft_strequ(ft_strchr(file_name + count, '.'), ".cor") == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int			is_champion(char *file_name, int *champ_size)
{
	char			buf[16 + CHAMP_MAX_SIZE + NAME_LEN + COM_LEN + 3];
	unsigned int	champ_file_min_size;
	unsigned int	bytes_read;
	unsigned int	magic;

	champ_file_min_size = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	if (check_for_cor_extension(file_name) == ERROR)
		return (print_message(FILE_MIS_COR, file_name, STDERR, ERROR));
	ft_bzero(buf, champ_file_min_size + CHAMP_MAX_SIZE + 3);
	bytes_read = read_champion(buf, file_name, champ_file_min_size + \
		CHAMP_MAX_SIZE);
	if (bytes_read == ERROR)
		return (ERROR);
	if (check_for_null_bytes(buf) == ERROR)
		return (print_message(FILE_INV_FORMAT, file_name, STDERR, ERROR));
	*champ_size = convert_to_int(buf + 8 + PROG_NAME_LENGTH);
	magic = convert_to_int(buf);
	if (*champ_size < -1 || CHAMP_MAX_SIZE < *champ_size || \
		bytes_read - champ_file_min_size != (unsigned int)*champ_size)
		return (print_message(FILE_CHAMP_TOO_BIG, file_name, STDERR, ERROR));
	if (magic != COREWAR_EXEC_MAGIC)
		return (print_message(FILE_INV_MAGIC, file_name, STDERR, ERROR));
	return (SUCCESS);
}
