/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_input_save_option.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/25 13:02:32 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/27 13:04:25 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>
#include <unistd.h>

static int	save_option_input(t_vm *vm, char **argv, int idx)
{
	long int	tmp;
	int			champ_size;

	tmp = ft_atoi(argv[idx + 1]);
	if (0 <= tmp && tmp <= FT_INT_MAX && ft_strchr(argv[idx], 'd') != NULL)
	{
		vm->dump = tmp;
		return (2);
	}
	champ_size = 0;
	if (0 <= tmp && tmp <= MAX_PLAYERS && ft_strchr(argv[idx], 'n') != NULL \
		&& is_champion(argv[idx + 2], &champ_size) == TRUE && \
		save_champion(vm, argv[idx + 2], champ_size, tmp) == TRUE)
		return (3);
	return (print_message(INV_OPT, argv[idx], STDERR));
}

int			save_option(t_vm *vm, char **argv, int idx, int argc)
{
	if (ft_strstr(argv[idx], ".cor") != NULL)
		return (1);
	if ((ft_strchr(argv[idx], 'd') != NULL || (ft_strchr(argv[idx], 'n') != NULL
		&& (idx + 2 < argc))) && ft_isint(argv[idx + 1]) == TRUE)
		return (save_option_input(vm, argv, idx));
	if (ft_strchr(argv[idx], 'v') || ft_strchr(argv[idx], 'a') \
		|| ft_strchr(argv[idx], 'b') || ft_strchr(argv[idx], 'c') \
		|| ft_strchr(argv[idx], 'e') || ft_strchr(argv[idx], 'f'))
	{
		if (ft_strchr(argv[idx], 'v') != NULL)
			vm->visualizer = TRUE;
		if (ft_strchr(argv[idx], 'a') != NULL)
			vm->a_option = TRUE;
		if (ft_strchr(argv[idx], 'b') != NULL)
			vm->b_option = TRUE;
		if (ft_strchr(argv[idx], 'c') != NULL)
			vm->c_option = TRUE;
		if (ft_strchr(argv[idx], 'e') != NULL)
			vm->e_option = TRUE;
		if (ft_strchr(argv[idx], 'f') != NULL)
			vm->f_option = TRUE;
		return (1);
	}
	return (print_message(INV_OPT, argv[idx], STDERR));
}
