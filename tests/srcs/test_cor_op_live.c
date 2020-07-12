/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_cor_op_live.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/12 15:41:59 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/12 16:19:12 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "corewar.h"

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

Test(cor_op_live, valid_id/* , .init=redirect_all_stdout */)
{
	t_vm vm;
	t_cursor *cursor;
	char	op_code = 1;
	int		move_bytes = 5;
	int		arg_1 = -2;
	unsigned int live_count = 5;
	unsigned int decay = 142;

	ft_bzero(&vm, sizeof(t_vm));
	cr_assert_eq(init_champions(&vm, 4), SUCCESS, "something went wrong when initializing the champs\n");
	vm.champ[2]->exec_code[0] = op_code;
	vm.champ[2]->exec_code[1] = ((unsigned char*)&arg_1)[3];
	vm.champ[2]->exec_code[2] = ((unsigned char*)&arg_1)[2];
	vm.champ[2]->exec_code[3] = ((unsigned char*)&arg_1)[1];
	vm.champ[2]->exec_code[4] = ((unsigned char*)&arg_1)[0];
	vm.champ[2]->header.prog_size = move_bytes;

	cr_assert_eq(cursors_init(&vm), SUCCESS, "something went wrong when initializing the cursors\n");	// creates cursor list from the champions and loads the exec code into the arena
	cursor = vm.cursors->next->next;
	vm.last_live = -4;
	vm.live_count = live_count;
	cursor->decay = decay;
	unsigned int pc_before = cursor->pc;
	op_live(&vm, cursor);
	unsigned int pc_after = cursor->pc;
	cr_expect_eq(vm.last_live, -2, "last live is still %d but should be %d", vm.last_live, arg_1);
	cr_expect_eq(vm.live_count, live_count + 1, "live_count is %d but should be %d\n", vm.live_count, live_count + 1);
	cr_expect_eq(cursor->decay, 0, "decay in cursor is %d but should be 0\n", cursor->decay);
	cr_assert_eq(pc_after - pc_before, move_bytes, "cursor moved %d bytes but should have moved %d bytes\n", pc_after - pc_before, move_bytes);
}
