/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/25 17:54:31 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/05/25 17:54:31 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>

int		print_message(char *message, char *info, int fd, int ret)
{
	if (info != NULL)
		ft_dprintf(fd, "%s:\n", info);
	ft_dprintf(fd, "%s", message);
	return (ret);
}

static void	free_champions(t_header ***champions)
{
	int		idx;

	idx = 1;
	while (idx <= MAX_PLAYERS)
	{
		if ((*champions)[idx] != NULL)
		{
			ft_bzero((*champions)[idx], sizeof(t_header));
			free((*champions)[idx]);
			(*champions)[idx] = NULL;
		}
		++idx;
	}
	*champions = NULL;
}

int		free_vm(t_vm *vm, int ret)
{
	if (vm->arena)
		ft_strdel(&(vm->arena));
	if (vm->champions)
		free_champions(&(vm->champions));
	// if (vm->cursor)
	// 	free_cursors(&(vm->cursor));
	return (ret);
}
