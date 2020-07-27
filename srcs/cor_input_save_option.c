/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_input_save_option.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/25 13:02:32 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/27 10:39:19 by nstabel       ########   odam.nl         */
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
	if (ft_strchr(argv[idx], 'v') != NULL)
	{
		vm->visualizer = TRUE;
		return (1);
	}	if (ft_strchr(argv[idx], 'a') != NULL)
	{
		vm->a_option = TRUE;
		return (1);
	}	if (ft_strchr(argv[idx], 'b') != NULL)
	{
		vm->b_option = TRUE;
		return (1);
	}
	if ((ft_strchr(argv[idx], 'd') != NULL || (ft_strchr(argv[idx], 'n') != NULL
		&& (idx + 2 < argc))) && ft_isint(argv[idx + 1]) == TRUE)
		return (save_option_input(vm, argv, idx));
	return (print_message(INV_OPT, argv[idx], STDERR));
}
