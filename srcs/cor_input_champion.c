/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_input_champion.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/26 11:58:03 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/05/26 11:58:03 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	check_for_champ_no(t_vm *vm, unsigned int *champ_no)
{
	if (*champ_no > MAX_PLAYERS)
		return (ERROR);
	if (vm->champions == NULL)
		vm->champions = (t_header**)ft_memalloc(sizeof(t_header*) * \
			MAX_PLAYERS + 1);
	if (vm->champions == NULL)
		return (ERROR);
	if (*champ_no > 0 && vm->champions[*champ_no] == NULL)
		return (SUCCESS);
	*champ_no = 1;
	while (*champ_no <= MAX_PLAYERS && vm->champions[*champ_no] != NULL)
		*champ_no += 1;
	if (*champ_no > MAX_PLAYERS)
		return (ERROR);
	return (SUCCESS);
}

static int	check_trailing_zeros(char *buf)
{
	int		position_1;
	int		position_2;

	position_1 = ft_strlen(buf + 4) + 4;
	position_2 = ft_strlen(buf + 12 + PROG_NAME_LENGTH) + 12 + PROG_NAME_LENGTH;
	while (position_1 - 4 < PROG_NAME_LENGTH || \
		position_2 - 12 - PROG_NAME_LENGTH < COMMENT_LENGTH)
	{
		if (position_1 - 4 < PROG_NAME_LENGTH && buf[position_1] != '\0')
			return (ERROR);
		if (position_2 - 12 - PROG_NAME_LENGTH < COMMENT_LENGTH && \
			buf[position_2] != '\0')
			return (ERROR);
		++position_1;
		++position_2;
	}
	return (SUCCESS);
}

int			save_champion(t_vm *vm, char *file, int champ_len,
			unsigned int champ_no)
{
	char			buf[16 + champ_len + PROG_NAME_LENGTH + COMMENT_LENGTH + 1];

	if (check_for_champ_no(vm, &champ_no) == ERROR)
		return (print_message(INV_OPT_N, file, STDERR, ERROR));
	read_champion(buf, file, 16 + champ_len + PROG_NAME_LENGTH + \
		COMMENT_LENGTH);
	if (check_trailing_zeros(buf) == ERROR)
		return (print_message(FILE_MIS_TRAIL_ZER, file, STDERR, ERROR));
	vm->champions[champ_no] = (t_header*)ft_memalloc(sizeof(t_header));
	vm->champions[champ_no]->magic = COREWAR_EXEC_MAGIC;
	vm->champions[champ_no]->prog_size = champ_len;
	ft_strncpy(vm->champions[champ_no]->prog_name, buf + 4, ft_strlen(buf + 4));
	ft_strncpy(vm->champions[champ_no]->comment, buf + 12 + PROG_NAME_LENGTH, \
		ft_strlen(buf + 12 + PROG_NAME_LENGTH));
	return (SUCCESS);
}
