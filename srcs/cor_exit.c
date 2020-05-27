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
#include "libft.h"
#include "cor_errors.h"

// static int	errors_init(char **errors)
// {
// 	errors[0] = USAGE;
// 	errors[1] = INV_OPT;
// 	errors[2] = INV_OPT_N_NO_TOO_BIG;
// 	errors[3] = INV_OPT_N_CHAMP_EXISTS;
// 	errors[4] = INT_FILE_NAME;
// 	errors[5] = FILE_NOT_EXIST;
// 	errors[6] = FILE_TOO_BIG;
// 	errors[7] = FILE_TOO_SMALL;
// 	errors[8] = FILE_INCORRECT_FORMAT;
// 	errors[9] = CHAMP_TOO_BIG;
// }

int		print_message(char *message, char *info, int fd, int ret)
{
	// char	*errors[10];

	// errors_init(errors);
	if (info != NULL)
		ft_dprintf(fd, "%s:\n", info);
	ft_dprintf(fd, "%s", message);
	return (ret);
}

int		free_vm(t_vm *vm, int ret)
{
	if (vm->arena)
		ft_strdel(&(vm->arena));
	// if (vm->champions)
	// 	free_champions(&(vm->champions));
	// if (vm->cursor)
	// 	free_cursors(&(vm->cursor));
	return (ret);
}
