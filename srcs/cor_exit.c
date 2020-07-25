/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/25 17:54:31 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/10 16:54:17 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>

int			print_message(char *message, char *info, int fd)
{
	if (info != NULL)
		ft_dprintf(fd, "%s:\n", info);
	ft_dprintf(fd, "%s", message);
	exit(0);
	return (ERROR);
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
			free((*champions)[idx]);
			(*champions)[idx] = NULL;
		}
		++idx;
	}
	*champions = NULL;
}

int			free_vm(t_vm *vm, int ret)
{
	t_cursor	*cursor_to_del;

	if (vm->champ)
		free_champions(&(vm->champ));
	while (vm->cursors)
	{
		cursor_to_del = vm->cursors;
		vm->cursors = cursor_to_del->next;
		ft_bzero(cursor_to_del, sizeof(t_cursor));
		free(cursor_to_del);
	}
	ft_bzero(vm, sizeof(t_vm));
	return (ret);
}
