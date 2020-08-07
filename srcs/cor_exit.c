/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/25 17:54:31 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/08/07 18:47:15 by mgross        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>

int			print_usage(int ret)
{
	ft_putstr("Usage: ./corewar [-d N -n N | -v ] <champion1.cor> ");
	ft_putstr("<...>\n\t-d N\t\t: Dumps memory after N cycles then exits\n");
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

int			free_vm(t_vm *vm, int ret)
{
	t_cursor	*cursor_to_del;
	(void)ret;
	//hier moeten we de ret nog aanpassen
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
