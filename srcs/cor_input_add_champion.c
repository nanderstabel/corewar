/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_input_add_champion.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/26 11:58:03 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/06 15:10:25 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	check_for_champ_no(t_vm *vm, unsigned int *champ_no)
{
	if (*champ_no > MAX_PLAYERS)
		return (print_message(INV_OPT_N, NULL, STDERR, ERROR));
	if (vm->champ == NULL)
		vm->champ = (t_champ**)ft_memalloc(sizeof(t_champ*) * \
			MAX_PLAYERS + 1);
	if (vm->champ == NULL)
		return (ERROR);
	if (*champ_no > 0 && vm->champ[*champ_no] == NULL)
		return (SUCCESS);
	*champ_no = 1;
	while (*champ_no <= MAX_PLAYERS && vm->champ[*champ_no] != NULL)
		*champ_no += 1;
	if (*champ_no > MAX_PLAYERS)
		return (print_message(TOO_MANY_CHAMPS, NULL, STDERR, ERROR));
	return (SUCCESS);
}

static int	check_trailing_zeros(unsigned char *buf)
{
	int		position_1;
	int		position_2;

	position_1 = ft_strlen((char*)buf + 4) + 4;
	position_2 = ft_strlen((char*)buf + 12 + PROG_NAME_LENGTH) + 12 + PROG_NAME_LENGTH;
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
	unsigned char	buf[16 + champ_len + PROG_NAME_LENGTH + COMMENT_LENGTH + 1];

	if (check_for_champ_no(vm, &champ_no) == ERROR)
		return (ERROR);
	read_champion(buf, file, 16 + champ_len + PROG_NAME_LENGTH + \
		COMMENT_LENGTH);
	if (check_trailing_zeros(buf) == ERROR)
		return (print_message(FILE_MIS_TRAIL_ZER, file, STDERR, ERROR));
	vm->champ[champ_no] = (t_champ*)ft_memalloc(sizeof(t_champ));
	if (vm->champ[champ_no] == NULL)
		return (ERROR);
	vm->champ[champ_no]->header.magic = COREWAR_EXEC_MAGIC;
	vm->champ[champ_no]->header.prog_size = champ_len;
	ft_strcpy(vm->champ[champ_no]->header.prog_name, (char*)buf + 4);
	ft_strcpy(vm->champ[champ_no]->header.comment, (char*)buf + 12 + PROG_NAME_LENGTH);
	ft_strcpy(vm->champ[champ_no]->exec_code, (char*)buf + 16 + PROG_NAME_LENGTH \
		+ COMMENT_LENGTH);
	vm->champ_count++;
	ft_strcpy(ft_strstr(file, ".cor"), "\0\0\0\0");
	return (SUCCESS);
}
