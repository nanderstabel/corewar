/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_input.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/21 10:38:30 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/06 12:23:10 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>
#include <unistd.h>

static int	last_check(t_vm *vm)
{
	unsigned int	idx;

	idx = 1;
	if (vm->champ_count > MAX_PLAYERS)
		return (ERROR);
	while (idx <= vm->champ_count)
	{
		if (vm->champ[idx] == NULL)
			return (print_message(INV_OPT, "-n", STDERR));
		++idx;
	}
	return (SUCCESS);
}

static int	does_file_exist(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (print_message(FILE_NOT_EXIST, str, STDERR));
	close(fd);
	return (SUCCESS);
}

static int	is_option_or_file(char *str)
{
	unsigned int	i;

	if (ft_strequ(str, "-dump") == SUCCESS)
		return (SUCCESS);
	if (str[0] != '-' && ft_strstr(str, ".cor"))
		return (does_file_exist(str));
	if (str[0] != '-' || str[0] == '\0')
		return (print_usage(ERROR));
	if (str[1] == '\0' || \
		(ft_strchr(str, 'n') != NULL && ft_strchr(str, 'd') != NULL))
		return (print_message(INV_OPT, str, STDERR));
	i = 1;
	while (str[i] != '\0')
	{
		if (ft_strchr(OPTIONS, str[i]) == NULL)
			return (print_message(INV_OPT, str, STDERR));
		++i;
	}
	return (SUCCESS);
}

int			input_validation(t_vm *vm, char **argv, int argc)
{
	int				idx;
	unsigned int	offset;
	int				champ_size;

	idx = 1;
	while (idx < argc)
	{
		offset = 0;
		if (is_option_or_file(argv[idx]) == FALSE)
			return (ERROR);
		offset = save_option(vm, argv, idx, argc);
		if (offset == 0)
			return (ERROR);
		idx += offset;
	}
	idx = 1;
	while (idx < argc)
	{
		champ_size = 0;
		if (is_champion(argv[idx], &champ_size) == SUCCESS && \
			save_champion(vm, argv[idx], champ_size, 0) == ERROR)
			return (ERROR);
		++idx;
	}
	return (last_check(vm));
}
