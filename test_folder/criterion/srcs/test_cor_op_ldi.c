/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_cor_op_ldi.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/12 13:05:35 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/17 14:16:56 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "corewar.h"

static void	redirect_all_stdout(void)
{
	// return ;
	cr_redirect_stdout();
	cr_redirect_stderr();
}

static int	init_champions(t_vm *vm, unsigned int champ_count)
{
	unsigned int idx;
    char *name;
    char *idx_str;

	idx = 1;
	vm->champ = (t_champ**)ft_memalloc(sizeof(t_champ*) * MAX_PLAYERS);
	if (vm->champ == NULL)
		return (ERROR);
	vm->champ_count = champ_count;
	while (idx <= champ_count)
	{
		vm->champ[idx] = (t_champ*)ft_memalloc(sizeof(t_champ));
		if (vm->champ[idx] == NULL)
			return (ERROR);
		vm->champ[idx]->id = -idx;
		vm->champ[idx]->header.magic = COREWAR_EXEC_MAGIC;
		idx_str = ft_itoa(idx);
		name = ft_strjoin("player", idx_str);
		ft_strcpy(vm->champ[idx]->header.prog_name, name);
		ft_strdel(&name);
		ft_strdel(&idx_str);
		vm->champ[idx]->header.prog_size = 0;
		ft_strcpy(vm->champ[idx]->header.comment, "I came here to test stuff");
		++idx;
	}
	return (SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////
//	REG_REG_REG    REG_REG_REG    REG_REG_REG    REG_REG_REG    REG_REG_REG	  //
////////////////////////////////////////////////////////////////////////////////

Test(cor_op_ldi, dir_reg_1, .init=redirect_all_stdout)
{
	t_vm vm;
	ft_bzero(&vm, sizeof(t_vm));
	t_cursor *cursor;
	unsigned char	op_code = 2;
	unsigned char	encoding = 0b01010100;
	unsigned char	arg_1 = 2;
	unsigned int	arg_1_len = 1;
	unsigned char	arg_2 = 3;
	unsigned int	arg_2_len = 1;
	unsigned char	arg_3 = 4;
	unsigned int	arg_3_len = 1;
	unsigned int	prog_size = 2 + arg_1_len + arg_2_len + arg_3_len;
	int				value = 420;
	int				address = (0x6969 + 0x0420) % IDX_MOD;
	unsigned int	champ_count = 3;
	unsigned int	champ_no = 1;

	// preparing the champion to test
	cr_assert_eq(init_champions(&vm, champ_count), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[champ_no]->exec_code[0] = op_code;
	vm.champ[champ_no]->exec_code[1] = encoding;
	store_in_arena(vm.champ[champ_no]->exec_code, 2, arg_1_len, arg_1);
	store_in_arena(vm.champ[champ_no]->exec_code, 2 + arg_1_len, arg_2_len, arg_2);
	store_in_arena(vm.champ[champ_no]->exec_code, 2 + arg_1_len + arg_2_len, arg_3_len, arg_3);
	vm.champ[champ_no]->header.prog_size = prog_size;

	store_in_arena(vm.arena, address, 4, value);
	// create cursor list from the champions and load the exec code into the arena
	cr_assert_eq(cursors_init(&vm), SUCCESS, "something went wrong when initializing the cursors\n");
	unsigned int count = champ_no;
	cursor = vm.cursors;
	while (count < champ_count)
	{
		cursor = cursor->next;
		++count;
	}
	cursor->reg[arg_1] = 0x6969;
	cursor->reg[arg_2] = 0x0420;
	cr_assert_eq(cursor->reg[(int)arg_3], 0, "reg[arg_3] = %d not initialized to 0\n", cursor->reg[(int)arg_3]);
	op_ldi(&vm, cursor);
	cr_assert_eq(cursor->reg[(int)arg_3], value, "stored: reg[arg_3] = %d\n expected: reg[arg_3] = %d", cursor->reg[(int)arg_3], value);
	// cr_assert_eq(cursor->reg[(int)arg_1], value, "stored: reg[arg_1] = %d\n expected: reg[arg_1] = %d", cursor->reg[(int)arg_1], value);
	cr_assert_eq(cursor->carry, 0, "carry: %d\n expected: %d", cursor->carry, 0);
}
