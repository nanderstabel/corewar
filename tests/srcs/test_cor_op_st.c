/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_cor_op_st.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/12 13:05:35 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/13 13:46:36 by lhageman      ########   odam.nl         */
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

Test(cor_op_st, reg_reg_1, .init=redirect_all_stdout)
{
	t_vm vm;
	t_cursor *cursor;
	char	op_code = 3;
	char	decoding = 80;
	int		move_bytes = 4;
	char	arg_1 = 2;
	char	arg_2 = 3;
	int		value = 42;

	ft_bzero(&vm, sizeof(t_vm));
	cr_assert_eq(init_champions(&vm, 1), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[1]->exec_code[0] = op_code;
	vm.champ[1]->exec_code[1] = decoding;
	// store the value of reg 1 in reg 2
	vm.champ[1]->exec_code[2] = arg_1;
	vm.champ[1]->exec_code[3] = arg_2;
	vm.champ[1]->header.prog_size = move_bytes;

	cr_assert_eq(cursors_init(&vm), SUCCESS, "something went wrong when initializing the cursors\n");	// creates cursor list from the champions and loads the exec code into the arena
	cursor = vm.cursors;
	unsigned int pc_before = cursor->pc;
	cursor->reg[(int)arg_1] = value;
	cr_assert_eq(cursor->reg[(int)arg_2], 0, "reg[arg_2] = %d not initialized to 0\n", cursor->reg[(int)arg_2]);
	op_st(&vm, cursor);
	unsigned int pc_after = cursor->pc;
	cr_assert_eq(cursor->reg[(int)arg_2], value, "reg[arg_2] = %d\n expected: reg[arg_2] = %d", cursor->reg[(int)arg_1], value);
	cr_assert_eq(pc_after - pc_before, move_bytes, "cursor moved %d bytes but should have moved %d bytes\n", pc_after - pc_before, move_bytes);
}


// Test(cor_op_st, reg_ind_1, .init=redirect_all_stdout)
// {
// 	t_vm vm;
// 	t_cursor *cursor;
// 	char	op_code = 3;
// 	char	decoding = 112;		// 01 11 00 00
// 	int		move_bytes = 5;
// 	char	arg_1 = 2;
// 	char	arg_2_byte_1 = 5;	
// 	char	arg_2_byte_2 = 10;
// 	int		value = 42;
// 	//01110000
// 	ft_bzero(&vm, sizeof(t_vm));
// 	cr_assert_eq(init_champions(&vm, 1), SUCCESS, "something went wrong when initializing the champs\n");
// 	vm.champ[1]->exec_code[0] = op_code;
// 	vm.champ[1]->exec_code[1] = decoding;
// 	// store the value of reg 1 in reg 2
// 	vm.champ[1]->exec_code[2] = arg_1;
// 	vm.champ[1]->exec_code[3] = arg_2_byte_1;
// 	vm.champ[1]->exec_code[4] = arg_2_byte_2;
// 	vm.champ[1]->header.prog_size = move_bytes;

// 	cr_assert_eq(cursors_init(&vm), SUCCESS, "something went wrong when initializing the cursors\n");	// creates cursor list from the champions and loads the exec code into the arena
// 	cursor = vm.cursors;
// 	int	arg_2 = convert_to_int(&(vm.arena[cursor->pc + 3]), 2);
// 	unsigned int pc_before = cursor->pc;
// 	cursor->reg[(int)arg_1] = value;
// 	unsigned int store_idx = new_idx(cursor->pc, arg_2, FALSE);
// 	cr_assert_eq((int)vm.arena[store_idx], 0, "arena at store_idx not initialized to 0\n");
// 	op_st(&vm, cursor);
// 	unsigned int pc_after = cursor->pc;
// 	cr_assert_eq((int)vm.arena[store_idx], value, "reg[arg_2] = %d\n expected: reg[arg_2] = %d", (int)vm.arena[store_idx], value);
// 	cr_assert_eq(pc_after - pc_before, move_bytes, "cursor moved %d bytes but should have moved %d bytes\n", pc_after - pc_before, move_bytes);
// }
