/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_cor_op_st.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/12 13:05:35 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/21 16:30:25 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "corewar.h"

static void	redirect_all_stdout(void)
{
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
//	REG_REG		REG_REG		REG_REG		REG_REG		REG_REG		REG_REG		  //
////////////////////////////////////////////////////////////////////////////////

Test(cor_op_st, reg_reg_inv_1, .init=redirect_all_stdout)
{
	t_vm vm;
	ft_bzero(&vm, sizeof(t_vm));
	t_cursor *cursor;
	unsigned char	op_code = 3;
	unsigned int	champ_count = 3;
	unsigned int	champ_no = 1;
	unsigned char	encoding = 80;		// 01 01 00 00
	unsigned int	prog_size = 4;
	unsigned char	arg_1 = 2;
	unsigned char	arg_2 = REG_NUMBER - 1;
	unsigned int	arg_2_len = 1;
	int				value = 4;

	// preparing the champion to test
	cr_assert_eq(init_champions(&vm, champ_count), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[champ_no]->exec_code[0] = op_code;
	vm.champ[champ_no]->exec_code[1] = encoding;
	vm.champ[champ_no]->exec_code[2] = arg_1;
	store_in_arena(vm.champ[champ_no]->exec_code, 3, arg_2_len, arg_2);
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
	cursor->reg[(int)arg_1] = value;
	cr_assert_eq(cursor->reg[(int)arg_2], 0, "reg[arg_2] = %d not initialized to 0\n", cursor->reg[(int)arg_2]);
	cr_assert_eq(op_st(&vm, cursor), SUCCESS, "op_st() returned ERROR with (REG)arg_1 = %d and (REG)arg_2 = %d\n", arg_1, arg_2);
	unsigned int pc_after = cursor->pc;
	cr_assert_eq(cursor->reg[(int)arg_2], value, "stored: reg[arg_2] = %d\n expected: reg[arg_2] = %d", cursor->reg[(int)arg_2], value);
	cr_assert_eq(cursor->reg[(int)arg_1], value, "stored: reg[arg_1] = %d\n expected: reg[arg_1] = %d", cursor->reg[(int)arg_1], value);
	cr_assert_eq(pc_after - pc_before, prog_size, "cursor moved %d bytes but should have moved %d bytes\n", pc_after - pc_before, prog_size);
}

Test(cor_op_st, reg_reg_4, .init=redirect_all_stdout)
{
	t_vm vm;
	ft_bzero(&vm, sizeof(t_vm));
	t_cursor *cursor;
	unsigned char	op_code = 3;
	unsigned int	champ_count = 3;
	unsigned int	champ_no = 1;
	unsigned char	encoding = 80;		// 01 01 00 00
	unsigned int	prog_size = 4;
	unsigned char	arg_1 = 2;
	unsigned char	arg_2 = REG_NUMBER;
	unsigned int	arg_2_len = 1;
	int				value = -4242;

	// preparing the champion to test
	cr_assert_eq(init_champions(&vm, champ_count), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[champ_no]->exec_code[0] = op_code;
	vm.champ[champ_no]->exec_code[1] = encoding;
	vm.champ[champ_no]->exec_code[2] = arg_1;
	store_in_arena(vm.champ[champ_no]->exec_code, 3, arg_2_len, arg_2);
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
	cursor->reg[(int)arg_1] = value;
	cr_assert_eq(cursor->reg[(int)arg_2], 0, "reg[arg_2] = %d not initialized to 0\n", cursor->reg[(int)arg_2]);
	cr_assert_eq(op_st(&vm, cursor), SUCCESS, "op_st() returned ERROR with (REG)arg_1 = %d and (REG)arg_2 = %d\n", arg_1, arg_2);
	unsigned int pc_after = cursor->pc;
	cr_assert_eq(cursor->reg[(int)arg_2], value, "stored: reg[arg_2] = %d\n expected: reg[arg_2] = %d", cursor->reg[(int)arg_2], value);
	cr_assert_eq(cursor->reg[(int)arg_1], value, "stored: reg[arg_1] = %d\n expected: reg[arg_1] = %d", cursor->reg[(int)arg_1], value);
	cr_assert_eq(pc_after - pc_before, prog_size, "cursor moved %d bytes but should have moved %d bytes\n", pc_after - pc_before, prog_size);
}

Test(cor_op_st, reg_reg_3, .init=redirect_all_stdout)
{
	t_vm vm;
	ft_bzero(&vm, sizeof(t_vm));
	t_cursor *cursor;
	unsigned char	op_code = 3;
	unsigned int	champ_count = 3;
	unsigned int	champ_no = 1;
	unsigned char	encoding = 80;		// 01 01 00 00
	unsigned int	prog_size = 4;
	unsigned char	arg_1 = REG_NUMBER;
	unsigned char	arg_2 = 1;
	unsigned int	arg_2_len = 1;
	int				value = 2;

	// preparing the champion to test
	cr_assert_eq(init_champions(&vm, champ_count), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[champ_no]->exec_code[0] = op_code;
	vm.champ[champ_no]->exec_code[1] = encoding;
	vm.champ[champ_no]->exec_code[2] = arg_1;
	store_in_arena(vm.champ[champ_no]->exec_code, 3, arg_2_len, arg_2);
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
	cursor->reg[(int)arg_1] = value;
	cr_assert_eq(cursor->reg[(int)arg_2], champ_no, "reg[%d] = %d not initialized to %d\n", arg_2, cursor->reg[(int)arg_2], champ_no);
	cr_assert_eq(op_st(&vm, cursor), SUCCESS, "op_st() returned ERROR with (REG)arg_1 = %d and (REG)arg_2 = %d\n", arg_1, arg_2);
	unsigned int pc_after = cursor->pc;
	cr_assert_eq(cursor->reg[(int)arg_2], value, "stored: reg[arg_2] = %d\n expected: reg[arg_2] = %d", cursor->reg[(int)arg_2], value);
	cr_assert_eq(pc_after - pc_before, prog_size, "cursor moved %d bytes but should have moved %d bytes\n", pc_after - pc_before, prog_size);
}

Test(cor_op_st, reg_reg_2, .init=redirect_all_stdout)
{
	t_vm vm;
	ft_bzero(&vm, sizeof(t_vm));
	t_cursor *cursor;
	unsigned char	op_code = 3;
	unsigned int	champ_count = 3;
	unsigned int	champ_no = 1;
	unsigned char	encoding = 80;		// 01 01 00 00
	unsigned int	prog_size = 4;
	unsigned char	arg_1 = 1;
	unsigned char	arg_2 = REG_NUMBER;
	unsigned int	arg_2_len = 1;
	int				value = -4;

	// preparing the champion to test
	cr_assert_eq(init_champions(&vm, champ_count), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[champ_no]->exec_code[0] = op_code;
	vm.champ[champ_no]->exec_code[1] = encoding;
	vm.champ[champ_no]->exec_code[2] = arg_1;
	store_in_arena(vm.champ[champ_no]->exec_code, 3, arg_2_len, arg_2);
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
	cursor->reg[(int)arg_1] = value;
	cr_assert_eq(cursor->reg[(int)arg_2], 0, "reg[arg_2] = %d not initialized to 0\n", cursor->reg[(int)arg_2]);
	cr_assert_eq(op_st(&vm, cursor), SUCCESS, "op_st() returned ERROR with (REG)arg_1 = %d and (REG)arg_2 = %d\n", arg_1, arg_2);
	unsigned int pc_after = cursor->pc;
	cr_assert_eq(cursor->reg[(int)arg_2], value, "stored: reg[arg_2] = %d\n expected: reg[arg_2] = %d", cursor->reg[(int)arg_2], value);
	cr_assert_eq(cursor->reg[(int)arg_1], value, "stored: reg[arg_1] = %d\n expected: reg[arg_1] = %d", cursor->reg[(int)arg_1], value);
	cr_assert_eq(pc_after - pc_before, prog_size, "cursor moved %d bytes but should have moved %d bytes\n", pc_after - pc_before, prog_size);
}

Test(cor_op_st, reg_reg_1, .init=redirect_all_stdout)
{
	t_vm vm;
	ft_bzero(&vm, sizeof(t_vm));
	t_cursor *cursor;
	unsigned char	op_code = 3;
	unsigned int	champ_count = 3;
	unsigned int	champ_no = 1;
	unsigned char	encoding = 80;		// 01 01 00 00
	unsigned int	prog_size = 4;
	unsigned char	arg_1 = 2;
	unsigned char	arg_2 = 3;
	unsigned int	arg_2_len = 1;
	int				value = 42;

	// preparing the champion to test
	cr_assert_eq(init_champions(&vm, champ_count), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[champ_no]->exec_code[0] = op_code;
	vm.champ[champ_no]->exec_code[1] = encoding;
	vm.champ[champ_no]->exec_code[2] = arg_1;
	store_in_arena(vm.champ[champ_no]->exec_code, 3, arg_2_len, arg_2);
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
	cursor->reg[(int)arg_1] = value;
	cr_assert_eq(cursor->reg[(int)arg_2], 0, "reg[arg_2] = %d not initialized to 0\n", cursor->reg[(int)arg_2]);
	cr_assert_eq(op_st(&vm, cursor), SUCCESS, "op_st() returned ERROR with (REG)arg_1 = %d and (REG)arg_2 = %d\n", arg_1, arg_2);
	unsigned int pc_after = cursor->pc;
	cr_assert_eq(cursor->reg[(int)arg_2], value, "stored: reg[arg_2] = %d\n expected: reg[arg_2] = %d", cursor->reg[(int)arg_2], value);
	cr_assert_eq(pc_after - pc_before, prog_size, "cursor moved %d bytes but should have moved %d bytes\n", pc_after - pc_before, prog_size);
}

////////////////////////////////////////////////////////////////////////////////
//	REG_IND		REG_IND		REG_IND		REG_IND		REG_IND		REG_IND		  //
////////////////////////////////////////////////////////////////////////////////

Test(cor_op_st, reg_ind_3, .init=redirect_all_stdout)
{
	t_vm vm;
	ft_bzero(&vm, sizeof(t_vm));
	t_cursor *cursor;
	unsigned char	op_code = 3;
	unsigned int	champ_count = 3;
	unsigned int	champ_no = 1;
	unsigned char	encoding = 112;		// 01 11 00 00
	unsigned int	prog_size = 5;
	unsigned char	arg_1 = 2;
	short			arg_2 = -5;
	unsigned int	arg_2_len = 2;
	int				value = 42;

	// preparing the champion to test
	cr_assert_eq(init_champions(&vm, champ_count), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[champ_no]->exec_code[0] = op_code;
	vm.champ[champ_no]->exec_code[1] = encoding;
	vm.champ[champ_no]->exec_code[2] = arg_1;
	store_in_arena(vm.champ[champ_no]->exec_code, 3, arg_2_len, arg_2);
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
	int	arg_2_read = convert_to_int(vm.arena, cursor->pc + 3, arg_2_len);
	cr_expect_eq(arg_2_read, arg_2, "arg_2_read: %d, arg_2: %d\n", arg_2_read, arg_2);
	unsigned int pc_before = cursor->pc;
	cursor->reg[(int)arg_1] = value;
	unsigned int store_idx = new_idx(cursor->pc, arg_2, FALSE);
	int	stored_value = convert_to_int(vm.arena, store_idx, 4);
	cr_assert_eq(stored_value, 0, "arena at store_idx not initialized to 0\n");
	cr_assert_eq(op_st(&vm, cursor), SUCCESS, "op_st() returned ERROR with (REG)arg_1 = %d and (IND)arg_2 = %d\n", arg_1, arg_2);
	unsigned int pc_after = cursor->pc;
	stored_value = convert_to_int(vm.arena, store_idx, 4);
	cr_assert_eq(stored_value, value, "stored_value = %d\n expected: real_value = %d", stored_value, value);
	cr_assert_eq(pc_after - pc_before, prog_size, "cursor moved %d bytes but should have moved %d bytes\n", pc_after - pc_before, prog_size);
}

Test(cor_op_st, reg_ind_2, .init=redirect_all_stdout)
{
	t_vm vm;
	ft_bzero(&vm, sizeof(t_vm));
	t_cursor *cursor;
	unsigned char	op_code = 3;
	unsigned int	champ_count = 3;
	unsigned int	champ_no = 1;
	unsigned char	encoding = 112;		// 01 11 00 00
	unsigned int	prog_size = 5;
	unsigned char	arg_1 = 2;
	short			arg_2 = 5;
	unsigned int	arg_2_len = 2;
	int				value = -42;

	// preparing the champion to test
	cr_assert_eq(init_champions(&vm, champ_count), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[champ_no]->exec_code[0] = op_code;
	vm.champ[champ_no]->exec_code[1] = encoding;
	vm.champ[champ_no]->exec_code[2] = arg_1;
	store_in_arena(vm.champ[champ_no]->exec_code, 3, arg_2_len, arg_2);
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
	int	arg_2_read = convert_to_int(vm.arena, cursor->pc + 3, arg_2_len);
	cr_expect_eq(arg_2_read, arg_2, "arg_2_read: %d, arg_2: %d\n", arg_2_read, arg_2);
	unsigned int pc_before = cursor->pc;
	cursor->reg[(int)arg_1] = value;
	unsigned int store_idx = new_idx(cursor->pc, arg_2, FALSE);
	int	stored_value = convert_to_int(vm.arena, store_idx, 4);
	cr_assert_eq(stored_value, 0, "arena at store_idx not initialized to 0\n");
	cr_assert_eq(op_st(&vm, cursor), SUCCESS, "op_st() returned ERROR with (REG)arg_1 = %d and (IND)arg_2 = %d\n", arg_1, arg_2);
	unsigned int pc_after = cursor->pc;
	stored_value = convert_to_int(vm.arena, store_idx, 4);
	cr_assert_eq(stored_value, value, "stored_value = %d\n expected: real_value = %d", stored_value, value);
	cr_assert_eq(pc_after - pc_before, prog_size, "cursor moved %d bytes but should have moved %d bytes\n", pc_after - pc_before, prog_size);
}

Test(cor_op_st, reg_ind_1, .init=redirect_all_stdout)
{
	t_vm vm;
	ft_bzero(&vm, sizeof(t_vm));
	t_cursor *cursor;
	unsigned char	op_code = 3;
	unsigned int	champ_count = 3;
	unsigned int	champ_no = 3;
	unsigned char	encoding = 0b01110000;
	unsigned int	prog_size = 5;
	unsigned char	arg_1 = 2;
	short			arg_2 = 5;
	unsigned int	arg_2_len = 2;
	int				value = 42;

	// preparing the champion to test
	cr_assert_eq(init_champions(&vm, champ_count), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[champ_no]->exec_code[0] = op_code;
	vm.champ[champ_no]->exec_code[1] = encoding;
	vm.champ[champ_no]->exec_code[2] = arg_1;
	store_in_arena(vm.champ[champ_no]->exec_code, 3, arg_2_len, arg_2);
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
	int	arg_2_read = convert_to_int(vm.arena, cursor->pc + 3, arg_2_len);
	cr_expect_eq(arg_2_read, arg_2, "arg_2_read: %d, arg_2: %d\n", arg_2_read, arg_2);
	unsigned int pc_before = cursor->pc;
	cursor->reg[(int)arg_1] = value;
	unsigned int store_idx = new_idx(cursor->pc, arg_2, FALSE);
	int	stored_value = convert_to_int(vm.arena, store_idx, 4);
	cr_assert_eq(stored_value, 0, "arena at store_idx not initialized to 0\n");
	cr_assert_eq(op_st(&vm, cursor), SUCCESS, "op_st() returned ERROR with (REG)arg_1 = %d and (IND)arg_2 = %d\n", arg_1, arg_2);
	unsigned int pc_after = cursor->pc;
	stored_value = convert_to_int(vm.arena, store_idx, 4);
	cr_assert_eq(stored_value, value, "stored_value = %d\n expected: real_value = %d", stored_value, value);
	cr_assert_eq(pc_after - pc_before, prog_size, "cursor moved %d bytes but should have moved %d bytes\n", pc_after - pc_before, prog_size);
}
