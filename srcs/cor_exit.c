/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/25 17:54:31 by mmarcell      #+#    #+#                 */
/*   Updated: 2021/09/13 17:30:45 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>

int			print_usage(int ret)
{
	ft_putstr("Usage: ./corewar [ -abcef | -d N -n N | -v ] <champion1.cor> ");
	ft_putstr("<...>\n\t-d N\t\t: Dumps memory after N cycles then exits\n");
	ft_putstr("\t-a  \t\t: Show operations (Params are NOT litteral ...)\n");
	ft_putstr("\t-b  \t\t: Show PC movements (Except for jumps)\n");
	ft_putstr("\t-c  \t\t: Show deaths\n");
	ft_putstr("\t-e  \t\t: Show cycles\n");
	ft_putstr("\t-f  \t\t: Show lives\n");
	ft_putstr("\t-v  \t\t: Use visualizer\n");
	return (ret);
}

int			print_message(char *message, char *info, int fd)
{
	if (info != NULL)
		ft_dprintf(fd, "%s:\n", info);
	ft_dprintf(fd, "%s", message);
	exit(0);
	return (0);
}

static void	free_champions(t_champ ***champions)
{
	int		idx;

	idx = 1;
	while (idx <= MAX_PLAYERS)
	{
		if ((*champions)[idx] != NULL)
		{
			ft_bzero((*champions)[idx], sizeof(t_champ));
			ft_memdel((void**)&(*champions)[idx]);
		}
		++idx;
	}
	ft_bzero(*champions, sizeof(t_champ*) * (MAX_PLAYERS + 1));
	ft_memdel((void**)champions);
}

int			free_vm(t_vm *vm)
{
	t_cursor	*cursor_to_del;

	if (vm->champ)
		free_champions(&(vm->champ));
	while (vm->cursors)
	{
		cursor_to_del = vm->cursors;
		vm->cursors = cursor_to_del->next;
		ft_bzero(cursor_to_del, sizeof(t_cursor));
		ft_memdel((void**)(&cursor_to_del));
	}
	ft_bzero(vm, sizeof(t_vm));
	return (0);
}
