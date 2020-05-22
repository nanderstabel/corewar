/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_input.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/21 10:38:30 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/05/21 10:38:30 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	is_option(char *str)
{
	int		i;

	if (ft_strchr(str, '.') || ft_strequ(str, "-dumb") == SUCCESS)
		return (SUCCESS);
	if (str[0] != '-' || str[0] == '\0')
		return (print_message(0, stderr, ERROR));
	if (str[1] == '\0')
		return (print_message(1, stderr, ERROR));
	if (ft_strchr(OPTIONS, 'n') != NULL && ft_strchr(OPTIONS, 'd') != NULL)
		return (print_message(1, stderr, ERROR));
	i = 1;
	while (str[i] != '\0')
	{
		if (ft_strchr(OPTIONS, str[i]) == NULL)
			return (print_message(1, stderr, ERROR));
		++i;
	}
	return (SUCCESS);
}

static int	save_option(t_vm *vm, char **argv, int idx, int argc)
{
	long int	tmp;
	int			champ_len;

	if (ft_strchr(argv[idx], '.') != NULL)
		return (1);
	if (ft_strchr(argv[idx], 'v') != NULL)
		vm->visualizer == TRUE;
	if ((ft_strchr(argv[idx], 'd') != NULL || ft_strchr(argv[idx], 'n') != NULL)
		&& (idx + 2 < argc) && ft_isint(argv[idx + 1]) == TRUE)
	{
		tmp = ft_atoi(argv[idx + 1]);
		if (tmp < 0 || INT_MAX < tmp)
			return (print_message(1, stderr, ERROR));
		if (ft_strchr(argv[idx], 'd') != NULL)
		{
			vm->dump = tmp;
			return (1);
		}
		champ_len = 0;
		if (is_champion(argv[idx + 2], &champ_len) == TRUE && \
			save_champion(vm, argv[idx + 2], champ_len, tmp) == TRUE)
			return (2);
	}
	return (print_message(1, stderr, ERROR));
}

int			input_validation(t_vm *vm, char **argv, int argc)
{
	int		idx;
	int		offset;
	int		champ_len;

	idx = 1;
	while (idx < argc)
	{
		offset = 0;
		if (is_option_or_file(argv[idx]) == FALSE)
			return (ERROR);
		offset = save_option(vm, argv, idx, argc);
		if (offset == 0)
			return (ERROR);
		idx += offset + 1;
	}
	idx = 1;
	while (idx < argc)
	{
		champ_len = 0;
		if (is_champion(argv[idx], &champ_len) == FALSE || \
			save_champion(vm, argv[idx], champ_len, 0) == ERROR)
			return (ERROR);
		++idx;
	}
	return (SUCCESS);
}
