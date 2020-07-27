/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_cor_op_ld.c                                   :+:    :+:            */
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
//	DIR_REG		DIR_REG		DIR_REG		DIR_REG		DIR_REG		DIR_REG		  //
////////////////////////////////////////////////////////////////////////////////

Test(cor_op_ld, dir_reg_1, .init=redirect_all_stdout)
{
	t_vm vm;
	ft_bzero(&vm, sizeof(t_vm));
	t_cursor *cursor;
	unsigned char	op_code = 2;
	unsigned char	encoding = 0b10010000;
	unsigned int	prog_size = 7;
	unsigned char	arg_1 = 0x69;
	unsigned int	arg_1_len = 4;
	unsigned char	arg_2 = REG_NUMBER - 1;
	unsigned int	arg_2_len = 1;
	int				value = 0;
	unsigned int	champ_count = 3;
	unsigned int	champ_no = 1;

	// preparing the champion to test
	cr_assert_eq(init_champions(&vm, champ_count), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[champ_no]->exec_code[0] = op_code;
	vm.champ[champ_no]->exec_code[1] = encoding;
	store_in_arena(vm.champ[champ_no]->exec_code, 2, arg_1_len, arg_1);
	store_in_arena(vm.champ[champ_no]->exec_code, 2 + arg_1_len, arg_2_len, arg_2);
	vm.champ[champ_no]->header.prog_size = prog_size;

	// create cursor list from the champions and load the exec code into the arena
	cr_assert_eq(cursors_init(&vm), SUCCESS, "something went wrong when initializing the cursors\n");
	unsigned int count = champ_no;
	cursor = vm.cursors;
	while (count < champ_count)
	{
		cursor = cursor->next;
		++count;
	}
	unsigned int pc_before = cursor->pc;
	cr_assert_eq(cursor->reg[(int)arg_2], 0, "reg[arg_2] = %d not initialized to 0\n", cursor->reg[(int)arg_2]);
	cr_assert_eq(op_ld(&vm, cursor), SUCCESS, "op_ld() returned ERROR with (DIR)arg_1 = %d and (REG)arg_2 = %d\n", arg_1, arg_2);
	unsigned int pc_after = cursor->pc;
	cr_assert_eq(cursor->reg[(int)arg_2], arg_1, "stored: reg[arg_2] = %d\n expected: reg[arg_2] = %d", cursor->reg[(int)arg_2], arg_1);
	// cr_assert_eq(cursor->reg[(int)arg_1], value, "stored: reg[arg_1] = %d\n expected: reg[arg_1] = %d", cursor->reg[(int)arg_1], value);
	cr_assert_eq(pc_after - pc_before, prog_size, "cursor moved %d bytes but should have moved %d bytes\n", pc_after - pc_before, prog_size);
	cr_assert_eq(cursor->carry, value, "carry: %d\n expected: %d", cursor->carry, value);
}

Test(cor_op_ld, dir_reg_2, .init=redirect_all_stdout)
{
	t_vm vm;
	ft_bzero(&vm, sizeof(t_vm));
	t_cursor *cursor;
	unsigned char	op_code = 2;
	unsigned char	encoding = 0b10010000;
	unsigned int	prog_size = 7;
	unsigned char	arg_1 = -69;
	unsigned int	arg_1_len = 4;
	unsigned char	arg_2 = REG_NUMBER - 1;
	unsigned int	arg_2_len = 1;
	int				value = 0;
	unsigned int	champ_count = 3;
	unsigned int	champ_no = 1;

	// preparing the champion to test
	cr_assert_eq(init_champions(&vm, champ_count), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[champ_no]->exec_code[0] = op_code;
	vm.champ[champ_no]->exec_code[1] = encoding;
	store_in_arena(vm.champ[champ_no]->exec_code, 2, arg_1_len, arg_1);
	store_in_arena(vm.champ[champ_no]->exec_code, 2 + arg_1_len, arg_2_len, arg_2);
	vm.champ[champ_no]->header.prog_size = prog_size;

	// create cursor list from the champions and load the exec code into the arena
	cr_assert_eq(cursors_init(&vm), SUCCESS, "something went wrong when initializing the cursors\n");
	unsigned int count = champ_no;
	cursor = vm.cursors;
	while (count < champ_count)
	{
		cursor = cursor->next;
		++count;
	}
	unsigned int pc_before = cursor->pc;
	cr_assert_eq(cursor->reg[(int)arg_2], 0, "reg[arg_2] = %d not initialized to 0\n", cursor->reg[(int)arg_2]);
	cr_assert_eq(op_ld(&vm, cursor), SUCCESS, "op_ld() returned ERROR with (DIR)arg_1 = %d and (REG)arg_2 = %d\n", arg_1, arg_2);
	unsigned int pc_after = cursor->pc;
	cr_assert_eq(cursor->reg[(int)arg_2], arg_1, "stored: reg[arg_2] = %d\n expected: reg[arg_2] = %d", cursor->reg[(int)arg_2], arg_1);
	// cr_assert_eq(cursor->reg[(int)arg_1], value, "stored: reg[arg_1] = %d\n expected: reg[arg_1] = %d", cursor->reg[(int)arg_1], value);
	cr_assert_eq(pc_after - pc_before, prog_size, "cursor moved %d bytes but should have moved %d bytes\n", pc_after - pc_before, prog_size);
	cr_assert_eq(cursor->carry, value, "carry: %d\n expected: %d", cursor->carry, value);
}

Test(cor_op_ld, dir_reg_carry, .init=redirect_all_stdout)
{
	t_vm vm;
	ft_bzero(&vm, sizeof(t_vm));
	t_cursor *cursor;
	unsigned char	op_code = 2;
	unsigned char	encoding = 0b10010000;
	unsigned int	prog_size = 7;
	unsigned char	arg_1 = 0x0;
	unsigned int	arg_1_len = 4;
	unsigned char	arg_2 = REG_NUMBER - 1;
	unsigned int	arg_2_len = 1;
	int				value = 1;
	unsigned int	champ_count = 3;
	unsigned int	champ_no = 1;

	// preparing the champion to test
	cr_assert_eq(init_champions(&vm, champ_count), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[champ_no]->exec_code[0] = op_code;
	vm.champ[champ_no]->exec_code[1] = encoding;
	store_in_arena(vm.champ[champ_no]->exec_code, 2, arg_1_len, arg_1);
	store_in_arena(vm.champ[champ_no]->exec_code, 2 + arg_1_len, arg_2_len, arg_2);
	vm.champ[champ_no]->header.prog_size = prog_size;

	// create cursor list from the champions and load the exec code into the arena
	cr_assert_eq(cursors_init(&vm), SUCCESS, "something went wrong when initializing the cursors\n");
	unsigned int count = champ_no;
	cursor = vm.cursors;
	while (count < champ_count)
	{
		cursor = cursor->next;
		++count;
	}
	unsigned int pc_before = cursor->pc;
	cr_assert_eq(cursor->reg[(int)arg_2], 0, "reg[arg_2] = %d not initialized to 0\n", cursor->reg[(int)arg_2]);
	cr_assert_eq(op_ld(&vm, cursor), SUCCESS, "op_ld() returned ERROR with (DIR)arg_1 = %d and (REG)arg_2 = %d\n", arg_1, arg_2);
	unsigned int pc_after = cursor->pc;
	cr_assert_eq(cursor->reg[(int)arg_2], arg_1, "stored: reg[arg_2] = %d\n expected: reg[arg_2] = %d", cursor->reg[(int)arg_2], arg_1);
	// cr_assert_eq(cursor->reg[(int)arg_1], value, "stored: reg[arg_1] = %d\n expected: reg[arg_1] = %d", cursor->reg[(int)arg_1], value);
	cr_assert_eq(pc_after - pc_before, prog_size, "cursor moved %d bytes but should have moved %d bytes\n", pc_after - pc_before, prog_size);
	cr_assert_eq(cursor->carry, value, "carry: %d\n expected: %d", cursor->carry, value);
}

Test(cor_op_ld, dir_reg_inv_1, .init=redirect_all_stdout)
{
	t_vm vm;
	ft_bzero(&vm, sizeof(t_vm));
	t_cursor *cursor;
	unsigned char	op_code = 2;
	unsigned char	encoding = 0b10010000;
	unsigned int	prog_size = 7;
	unsigned char	arg_1 = 0x69;
	unsigned int	arg_1_len = 4;
	unsigned char	arg_2 = - 1;
	unsigned int	arg_2_len = 1;
	// int				value = 4;
	unsigned int	champ_count = 3;
	unsigned int	champ_no = 1;

	// preparing the champion to test
	cr_assert_eq(init_champions(&vm, champ_count), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[champ_no]->exec_code[0] = op_code;
	vm.champ[champ_no]->exec_code[1] = encoding;
	store_in_arena(vm.champ[champ_no]->exec_code, 2, arg_1_len, arg_1);
	store_in_arena(vm.champ[champ_no]->exec_code, 2 + arg_1_len, arg_2_len, arg_2);
	vm.champ[champ_no]->header.prog_size = prog_size;

	// create cursor list from the champions and load the exec code into the arena
	cr_assert_eq(cursors_init(&vm), SUCCESS, "something went wrong when initializing the cursors\n");
	unsigned int count = champ_no;
	cursor = vm.cursors;
	while (count < champ_count)
	{
		cursor = cursor->next;
		++count;
	}
	unsigned int pc_before = cursor->pc;
	cr_assert_eq(cursor->reg[(int)arg_2], 0, "reg[arg_2] = %d not initialized to 0\n", cursor->reg[(int)arg_2]);
	cr_assert_eq(op_ld(&vm, cursor), ERROR, "op_ld() did not return ERROR with (DIR)arg_1 = %d and (REG)arg_2 = %d\n", arg_1, arg_2);
	unsigned int pc_after = cursor->pc;
	cr_assert_eq(pc_after - pc_before, 0, "cursor moved %d bytes but should have moved %d bytes\n", pc_after - pc_before, 0);
}

////////////////////////////////////////////////////////////////////////////////
//	IND_REG		IND_REG		IND_REG		IND_REG		IND_REG		IND_REG		  //
////////////////////////////////////////////////////////////////////////////////

Test(cor_op_ld, ind_reg_1, .init=redirect_all_stdout)
{
	t_vm vm;
	ft_bzero(&vm, sizeof(t_vm));
	t_cursor *cursor;
	unsigned char	op_code = 2;
	unsigned char	encoding = 0b11010000;
	unsigned int	prog_size = 5;
	unsigned char	arg_1 = 1;
	unsigned int	arg_1_len = 2;
	unsigned char	arg_2 = REG_NUMBER - 2;
	unsigned int	arg_2_len = 1;
	int				value = 3489661198;
	unsigned int	champ_count = 3;
	unsigned int	champ_no = 1;

	// preparing the champion to test
	cr_assert_eq(init_champions(&vm, champ_count), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[champ_no]->exec_code[0] = op_code;
	vm.champ[champ_no]->exec_code[1] = encoding;
	store_in_arena(vm.champ[champ_no]->exec_code, 2, arg_1_len, arg_1);
	store_in_arena(vm.champ[champ_no]->exec_code, 2 + arg_1_len, arg_2_len, arg_2);
	vm.champ[champ_no]->header.prog_size = prog_size;

	// create cursor list from the champions and load the exec code into the arena
	cr_assert_eq(cursors_init(&vm), SUCCESS, "something went wrong when initializing the cursors\n");
	unsigned int count = champ_no;
	cursor = vm.cursors;
	while (count < champ_count)
	{
		cursor = cursor->next;
		++count;
	}
	unsigned int pc_before = cursor->pc;
	cr_assert_eq(cursor->reg[(int)arg_2], 0, "reg[arg_2] = %d not initialized to 0\n", cursor->reg[(int)arg_2]);
	cr_assert_eq(op_ld(&vm, cursor), SUCCESS, "op_ld() returned ERROR with (DIR)arg_1 = %d and (REG)arg_2 = %d\n", arg_1, arg_2);
	unsigned int pc_after = cursor->pc;
	cr_assert_eq(cursor->reg[(int)arg_2], value, "stored: reg[arg_2] = %u\n expected: reg[arg_2] = %u", cursor->reg[(int)arg_2], value);
	// cr_assert_eq(cursor->reg[(int)arg_1], value, "stored: reg[arg_1] = %d\n expected: reg[arg_1] = %d", cursor->reg[(int)arg_1], value);
	cr_assert_eq(pc_after - pc_before, prog_size, "cursor moved %d bytes but should have moved %d bytes\n", pc_after - pc_before, prog_size);
	cr_assert_eq(cursor->carry, 0, "carry: %d\n expected: %d", cursor->carry, 0);
}
