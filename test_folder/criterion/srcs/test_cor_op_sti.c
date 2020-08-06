/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_cor_op_sti.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/21 14:23:42 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/21 18:18:48 by lhageman      ########   odam.nl         */
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
//	REG_REG_IND		REG_REG_IND		REG_REG_IND		REG_REG_IND				  //
////////////////////////////////////////////////////////////////////////////////

Test(cor_op_sti, reg_reg_ind_1, .init=redirect_all_stdout)
{
	t_vm vm;
	ft_bzero(&vm, sizeof(t_vm));
	t_cursor *cursor;
	unsigned char	op_code = 3;
	unsigned int	champ_count = 3;
	unsigned int	champ_no = 1;
	unsigned int	champ_pos = (MEM_SIZE / champ_count) * (champ_no - 1);
	unsigned char	encoding = 0b01011000;
	unsigned char	arg_1 = 2;
	unsigned int	arg_1_len = 1;
	int				arg_1_value = -4242;
	unsigned char	arg_2 = REG_NUMBER - 1;
	unsigned int	arg_2_len = 1;
	int				arg_2_value = 42;
	short			arg_3 = 42;
	unsigned int	arg_3_len = 2;
	unsigned int	prog_size = 2 + arg_1_len + arg_2_len + arg_3_len;
	unsigned int	expected_store_idx = new_idx(champ_pos, arg_2_value + arg_3, FALSE);

	// preparing the champion to test
	cr_assert_eq(init_champions(&vm, champ_count), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[champ_no]->exec_code[0] = op_code;
	vm.champ[champ_no]->exec_code[1] = encoding;
	store_in_arena(vm.champ[champ_no]->exec_code, 2, arg_1_len, arg_1);
	store_in_arena(vm.champ[champ_no]->exec_code, 3, arg_2_len, arg_2);
	store_in_arena(vm.champ[champ_no]->exec_code, 3 + arg_2_len, arg_3_len, arg_3);
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
	cursor->reg[(int)arg_1] = arg_1_value;
	cursor->reg[(int)arg_2] = arg_2_value;
	op_sti(&vm, cursor);
	int	store_idx = new_idx(champ_pos, cursor->reg[arg_2] + convert_to_int(vm.arena, champ_pos + 3 + arg_2_len, 2), FALSE);
	cr_assert_eq(store_idx, expected_store_idx, "store_idx = %d, expected_store_idx = %d\n", store_idx, expected_store_idx);
	int stored_value = convert_to_int(vm.arena, store_idx, 4);
	cr_assert_eq(stored_value, arg_1_value, "stored = %d\n expected = %d", stored_value, arg_1_value);
}

////////////////////////////////////////////////////////////////////////////////
//	REG_REG_DIR		REG_REG_DIR		REG_REG_DIR		REG_REG_DIR				  //
////////////////////////////////////////////////////////////////////////////////

Test(cor_op_sti, reg_reg_dir_3, .init=redirect_all_stdout)
{
	t_vm vm;
	ft_bzero(&vm, sizeof(t_vm));
	t_cursor *cursor;
	unsigned char	op_code = 3;
	unsigned int	champ_count = 4;
	unsigned int	champ_no = 2;
	unsigned int	champ_pos = (MEM_SIZE / champ_count) * (champ_no - 1);
	unsigned char	encoding = 0b01011000;
	unsigned char	arg_1 = 2;
	unsigned int	arg_1_len = 1;
	int				arg_1_value = -4242;
	unsigned char	arg_2 = REG_NUMBER - 1;
	unsigned int	arg_2_len = 1;
	int				arg_2_value = -42;
	short			arg_3 = -42;
	unsigned int	arg_3_len = 2;
	unsigned int	prog_size = 2 + arg_1_len + arg_2_len + arg_3_len;
	unsigned int	expected_store_idx = new_idx(champ_pos, arg_2_value + arg_3, FALSE);

	// preparing the champion to test
	cr_assert_eq(init_champions(&vm, champ_count), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[champ_no]->exec_code[0] = op_code;
	vm.champ[champ_no]->exec_code[1] = encoding;
	store_in_arena(vm.champ[champ_no]->exec_code, 2, arg_1_len, arg_1);
	store_in_arena(vm.champ[champ_no]->exec_code, 3, arg_2_len, arg_2);
	store_in_arena(vm.champ[champ_no]->exec_code, 3 + arg_2_len, arg_3_len, arg_3);
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
	cursor->reg[(int)arg_1] = arg_1_value;
	cursor->reg[(int)arg_2] = arg_2_value;
	op_sti(&vm, cursor);
	int	store_idx = new_idx(champ_pos, cursor->reg[arg_2] + convert_to_int(vm.arena, champ_pos + 3 + arg_2_len, 2), FALSE);
	cr_assert_eq(store_idx, expected_store_idx, "store_idx = %d, expected_store_idx = %d, pc = %d, champ_pos = %d\n", store_idx, expected_store_idx, cursor->pc, champ_pos);
	int stored_value = convert_to_int(vm.arena, store_idx, 4);
	cr_assert_eq(stored_value, arg_1_value, "stored = %d\n expected = %d", stored_value, arg_1_value);
}

Test(cor_op_sti, reg_reg_dir_2, .init=redirect_all_stdout)
{
	t_vm vm;
	ft_bzero(&vm, sizeof(t_vm));
	t_cursor *cursor;
	unsigned char	op_code = 3;
	unsigned int	champ_count = 3;
	unsigned int	champ_no = 1;
	unsigned int	champ_pos = (MEM_SIZE / champ_count) * (champ_no - 1);
	unsigned char	encoding = 0b01011000;
	unsigned char	arg_1 = 2;
	unsigned int	arg_1_len = 1;
	int				arg_1_value = -4242;
	unsigned char	arg_2 = REG_NUMBER - 1;
	unsigned int	arg_2_len = 1;
	int				arg_2_value = 42;
	short			arg_3 = 42;
	unsigned int	arg_3_len = 2;
	unsigned int	prog_size = 2 + arg_1_len + arg_2_len + arg_3_len;
	unsigned int	expected_store_idx = new_idx(champ_pos, arg_2_value + arg_3, FALSE);

	// preparing the champion to test
	cr_assert_eq(init_champions(&vm, champ_count), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[champ_no]->exec_code[0] = op_code;
	vm.champ[champ_no]->exec_code[1] = encoding;
	store_in_arena(vm.champ[champ_no]->exec_code, 2, arg_1_len, arg_1);
	store_in_arena(vm.champ[champ_no]->exec_code, 3, arg_2_len, arg_2);
	store_in_arena(vm.champ[champ_no]->exec_code, 3 + arg_2_len, arg_3_len, arg_3);
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
	cursor->reg[(int)arg_1] = arg_1_value;
	cursor->reg[(int)arg_2] = arg_2_value;
	op_sti(&vm, cursor);
	int	store_idx = new_idx(champ_pos, cursor->reg[arg_2] + convert_to_int(vm.arena, champ_pos + 3 + arg_2_len, 2), FALSE);
	cr_assert_eq(store_idx, expected_store_idx, "store_idx = %d, expected_store_idx = %d\n", store_idx, expected_store_idx);
	int stored_value = convert_to_int(vm.arena, store_idx, 4);
	cr_assert_eq(stored_value, arg_1_value, "stored = %d\n expected = %d", stored_value, arg_1_value);
}

Test(cor_op_sti, reg_reg_dir_1, .init=redirect_all_stdout)
{
	t_vm vm;
	ft_bzero(&vm, sizeof(t_vm));
	t_cursor *cursor;
	unsigned char	op_code = 3;
	unsigned int	champ_count = 3;
	unsigned int	champ_no = 1;
	unsigned int	champ_pos = (MEM_SIZE / champ_count) * (champ_no - 1);
	unsigned char	encoding = 0b01011000;
	unsigned char	arg_1 = 2;
	unsigned int	arg_1_len = 1;
	int				arg_1_value = -4242;
	unsigned char	arg_2 = REG_NUMBER - 1;
	unsigned int	arg_2_len = 1;
	int				arg_2_value = -42;
	short			arg_3 = 42;
	unsigned int	arg_3_len = 2;
	unsigned int	prog_size = 2 + arg_1_len + arg_2_len + arg_3_len;
	unsigned int	expected_store_idx = new_idx(champ_pos, arg_2_value + arg_3, FALSE);

	// preparing the champion to test
	cr_assert_eq(init_champions(&vm, champ_count), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[champ_no]->exec_code[0] = op_code;
	vm.champ[champ_no]->exec_code[1] = encoding;
	store_in_arena(vm.champ[champ_no]->exec_code, 2, arg_1_len, arg_1);
	store_in_arena(vm.champ[champ_no]->exec_code, 3, arg_2_len, arg_2);
	store_in_arena(vm.champ[champ_no]->exec_code, 3 + arg_2_len, arg_3_len, arg_3);
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
	cursor->reg[(int)arg_1] = arg_1_value;
	cursor->reg[(int)arg_2] = arg_2_value;
	op_sti(&vm, cursor);
	int	store_idx = new_idx(champ_pos, cursor->reg[arg_2] + convert_to_int(vm.arena, champ_pos + 3 + arg_2_len, 2), FALSE);
	cr_assert_eq(store_idx, expected_store_idx, "store_idx = %d, expected_store_idx = %d\n", store_idx, expected_store_idx);
	int stored_value = convert_to_int(vm.arena, store_idx, 4);
	cr_assert_eq(stored_value, arg_1_value, "stored = %d\n expected = %d", stored_value, arg_1_value);
}

