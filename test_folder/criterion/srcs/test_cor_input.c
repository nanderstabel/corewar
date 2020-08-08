#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "corewar.h"

static void	redirect_all_stdout(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

//TODO
// invalid tests:
//	NULL bytes at incorrect location
//	compromised magic number
//	exec code size too high
//	file too big
//	file too small
//	no trailing zeros after name or comment

// valid tests:
//	-v flag
//	champion file located multiple repositories up
//	champ exec code in arena
//	add to existing tests: check for correct exec code

///////////////////////////////////////////////////////////////////////////////
//	INVALID		INVALID		INVALID		INVALID		INVALID		INVALID		 //
///////////////////////////////////////////////////////////////////////////////

Test(input_validation, invalid_d_and_n, .init=redirect_all_stdout)
{
	int			expected_return = ERROR;
	int			expected_output_fd = STDERR;
	char		*expected_output = "-nd:\ninvalid option\n";
	int			given_argc = 7;
	char		**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);
	long int	dump = 6;

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("-nd");
	given_argv[2] = ft_itoa(dump);
	given_argv[3] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/fluttershy.cor");
	given_argv[4] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/helltrain.cor");
	given_argv[5] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bigzork.cor");
	given_argv[6] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bee_gees.cor");

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "error when validation input");
	if (expected_output_fd == STDOUT)
		cr_assert_stdout_eq_str(expected_output, "");
	if (expected_output_fd == STDERR)
		cr_assert_stderr_eq_str(expected_output, "");
	free_vm(&vm);
}

Test(input_validation, invalid_d_option_too_big, .init=redirect_all_stdout)
{
	int			expected_return = ERROR;
	int			expected_output_fd = STDERR;
	char		*expected_output = "-d:\ninvalid option\n";
	int			given_argc = 7;
	char		**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);
	long int	dump = 2680780788742;

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("-d");
	given_argv[2] = ft_itoa(dump);
	given_argv[3] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/fluttershy.cor");
	given_argv[4] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/helltrain.cor");
	given_argv[5] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bigzork.cor");
	given_argv[6] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bee_gees.cor");

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "error when validation input");
	if (expected_output_fd == STDOUT)
		cr_assert_stdout_eq_str(expected_output, "");
	if (expected_output_fd == STDERR)
		cr_assert_stderr_eq_str(expected_output, "");
	free_vm(&vm);
}

Test(input_validation, invalid_d_option_neg, .init=redirect_all_stdout)
{
	int		expected_return = ERROR;
	int		expected_output_fd = STDERR;
	char	*expected_output = "-d:\ninvalid option\n";
	int		given_argc = 7;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);
	int		dump = -2;

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("-d");
	given_argv[2] = ft_itoa(dump);
	given_argv[3] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/fluttershy.cor");
	given_argv[4] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/helltrain.cor");
	given_argv[5] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bigzork.cor");
	given_argv[6] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bee_gees.cor");

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "error when validation input");
	if (expected_output_fd == STDOUT)
		cr_assert_stdout_eq_str(expected_output, "");
	if (expected_output_fd == STDERR)
		cr_assert_stderr_eq_str(expected_output, "");
	free_vm(&vm);
}

Test(input_validation, invalid_n_option_two_players, .init=redirect_all_stdout)
{
	int		expected_return = ERROR;
	int		expected_output_fd = STDERR;
	char	*expected_output = "-n:\ninvalid option\n";
	int		given_argc = 5;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("-n");
	given_argv[2] = ft_strdup("4");
	given_argv[3] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/fluttershy.cor");
	given_argv[4] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/helltrain.cor");

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "'-n 4' with only two players should return ERROR");
	if (expected_output_fd == STDOUT)
		cr_assert_stdout_eq_str(expected_output, "");
	if (expected_output_fd == STDERR)
		cr_assert_stderr_eq_str(expected_output, "");
	free_vm(&vm);
}

Test(input_validation, invalid_n_option_four_players_1, .init=redirect_all_stdout)
{
	int		expected_return = ERROR;
	int		expected_output_fd = STDERR;
	char	*expected_output = "-n:\ninvalid option\n";
	int		given_argc = 13;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("-n");
	given_argv[2] = ft_strdup("4");
	given_argv[3] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/fluttershy.cor");
	given_argv[4] = ft_strdup("-n");
	given_argv[5] = ft_strdup("5");
	given_argv[6] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/helltrain.cor");
	given_argv[7] = ft_strdup("-n");
	given_argv[8] = ft_strdup("2");
	given_argv[9] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bigzork.cor");
	given_argv[10] = ft_strdup("-n");
	given_argv[11] = ft_strdup("3");
	given_argv[12] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bee_gees.cor");

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "'-n 5' should return ERROR");
	if (expected_output_fd == STDOUT)
		cr_assert_stdout_eq_str(expected_output, "");
	if (expected_output_fd == STDERR)
		cr_assert_stderr_eq_str(expected_output, "");
	free_vm(&vm);
}

Test(input_validation, invalid_five_players, .init=redirect_all_stdout)
{
	int		expected_return = ERROR;
	int		expected_output_fd = STDERR;
	char	*expected_output = TOO_MANY_CHAMPS;

	int		given_argc = 6;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/zork.cor");
	given_argv[2] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bigzork.cor");
	given_argv[3] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/fluttershy.cor");
	given_argv[4] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bee_gees.cor");
	given_argv[5] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/turtle.cor");

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "with four valid champions given, input validation returned %d when the expected return is %d", expected_return, real_return);

	if (expected_output_fd == STDOUT)
		cr_assert_stdout_eq_str(expected_output, "");
	if (expected_output_fd == STDERR)
		cr_assert_stderr_eq_str(expected_output, "");
		free_vm(&vm);
}


///////////////////////////////////////////////////////////////////////////////
//		VALID		VALID		VALID		VALID		VALID		VALID	 //
///////////////////////////////////////////////////////////////////////////////

Test(input_validation, valid_d_and_n_option_four_players)
{
	int		expected_return = SUCCESS;
	int		given_argc = 15;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);
	int		dump = 4;

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("-dump");
	given_argv[2] = ft_itoa(dump);
	given_argv[3] = ft_strdup("-n");
	given_argv[4] = ft_strdup("4");
	given_argv[5] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/fluttershy.cor");
	given_argv[6] = ft_strdup("-n");
	given_argv[7] = ft_strdup("1");
	given_argv[8] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/helltrain.cor");
	given_argv[9] = ft_strdup("-n");
	given_argv[10] = ft_strdup("2");
	given_argv[11] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bigzork.cor");
	given_argv[12] = ft_strdup("-n");
	given_argv[13] = ft_strdup("3");
	given_argv[14] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bee_gees.cor");

	char	*player_1 = "helltrain";
	char	*player_2 = "bigzork";
	char	*player_3 = "stayin' alive";
	char	*player_4 = "fluttershy";

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "error when validation input");
	cr_expect_eq(vm.dump, dump, "dump expected: %d, dump saved: %d", dump, vm.dump);
	cr_expect_str_eq(vm.champ[1]->header.prog_name, player_1, "player_1 expected: %s, player_1 saved: %s", player_1, vm.champ[1]->header.prog_name);
	cr_expect_str_eq(vm.champ[2]->header.prog_name, player_2, "player_2 expected: %s, player_2 saved: %s", player_2, vm.champ[2]->header.prog_name);
	cr_expect_str_eq(vm.champ[3]->header.prog_name, player_3, "player_3 expected: %s, player_3 saved: %s", player_3, vm.champ[3]->header.prog_name);
	cr_expect_str_eq(vm.champ[4]->header.prog_name, player_4, "player_4 expected: %s, player_4 saved: %s", player_4, vm.champ[4]->header.prog_name);
	free_vm(&vm);
}

Test(input_validation, valid_d_option_four_players_3)
{
	int		expected_return = SUCCESS;
	int		given_argc = 7;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);
	int		dump = 4;

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/fluttershy.cor");
	given_argv[2] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/helltrain.cor");
	given_argv[3] = ft_strdup("-d");
	given_argv[4] = ft_itoa(dump);
	given_argv[5] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bigzork.cor");
	given_argv[6] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bee_gees.cor");

	char	*player_1 = "fluttershy";
	char	*player_2 = "helltrain";
	char	*player_3 = "bigzork";
	char	*player_4 = "stayin' alive";

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "error when validation input");
	cr_expect_eq(vm.dump, dump, "dump expected: %d, dump saved: %d", dump, vm.dump);
	cr_expect_str_eq(vm.champ[1]->header.prog_name, player_1, "player_1 expected: %s, player_1 saved: %s", player_1, vm.champ[1]->header.prog_name);
	cr_expect_str_eq(vm.champ[2]->header.prog_name, player_2, "player_2 expected: %s, player_2 saved: %s", player_2, vm.champ[2]->header.prog_name);
	cr_expect_str_eq(vm.champ[3]->header.prog_name, player_3, "player_3 expected: %s, player_3 saved: %s", player_3, vm.champ[3]->header.prog_name);
	cr_expect_str_eq(vm.champ[4]->header.prog_name, player_4, "player_4 expected: %s, player_4 saved: %s", player_4, vm.champ[4]->header.prog_name);
	free_vm(&vm);
}

Test(input_validation, valid_d_option_four_players_2)
{
	int		expected_return = SUCCESS;
	int		given_argc = 7;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);
	int		dump = 4;

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/fluttershy.cor");
	given_argv[2] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/helltrain.cor");
	given_argv[3] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bigzork.cor");
	given_argv[4] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bee_gees.cor");
	given_argv[5] = ft_strdup("-d");
	given_argv[6] = ft_itoa(dump);

	char	*player_1 = "fluttershy";
	char	*player_2 = "helltrain";
	char	*player_3 = "bigzork";
	char	*player_4 = "stayin' alive";

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "error when validation input");
	cr_expect_eq(vm.dump, dump, "dump expected: %d, dump saved: %d", dump, vm.dump);
	cr_expect_str_eq(vm.champ[1]->header.prog_name, player_1, "player_1 expected: %s, player_1 saved: %s", player_1, vm.champ[1]->header.prog_name);
	cr_expect_str_eq(vm.champ[2]->header.prog_name, player_2, "player_2 expected: %s, player_2 saved: %s", player_2, vm.champ[2]->header.prog_name);
	cr_expect_str_eq(vm.champ[3]->header.prog_name, player_3, "player_3 expected: %s, player_3 saved: %s", player_3, vm.champ[3]->header.prog_name);
	cr_expect_str_eq(vm.champ[4]->header.prog_name, player_4, "player_4 expected: %s, player_4 saved: %s", player_4, vm.champ[4]->header.prog_name);
	free_vm(&vm);
}

Test(input_validation, valid_d_option_four_players_1)
{
	int		expected_return = SUCCESS;
	int		given_argc = 7;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);
	int		dump = 0;

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("-d");
	given_argv[2] = ft_itoa(dump);
	given_argv[3] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/fluttershy.cor");
	given_argv[4] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/helltrain.cor");
	given_argv[5] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bigzork.cor");
	given_argv[6] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bee_gees.cor");

	char	*player_1 = "fluttershy";
	char	*player_2 = "helltrain";
	char	*player_3 = "bigzork";
	char	*player_4 = "stayin' alive";

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "error when validation input");
	cr_expect_eq(vm.dump, dump, "dump expected: %d, dump saved: %d", dump, vm.dump);
	cr_expect_str_eq(vm.champ[1]->header.prog_name, player_1, "player_1 expected: %s, player_1 saved: %s", player_1, vm.champ[1]->header.prog_name);
	cr_expect_str_eq(vm.champ[2]->header.prog_name, player_2, "player_2 expected: %s, player_2 saved: %s", player_2, vm.champ[2]->header.prog_name);
	cr_expect_str_eq(vm.champ[3]->header.prog_name, player_3, "player_3 expected: %s, player_3 saved: %s", player_3, vm.champ[3]->header.prog_name);
	cr_expect_str_eq(vm.champ[4]->header.prog_name, player_4, "player_4 expected: %s, player_4 saved: %s", player_4, vm.champ[4]->header.prog_name);
	free_vm(&vm);
}

Test(input_validation, valid_d_option_two_players)
{
	int		expected_return = SUCCESS;
	int		given_argc = 5;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);
	int		dump = 4;

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("-d");
	given_argv[2] = ft_itoa(dump);
	given_argv[3] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/zork.cor");
	given_argv[4] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bigzork.cor");

	char	*player_1 = "zork";
	char	*player_2 = "bigzork";

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "error when validation input");
	cr_expect_eq(vm.dump, dump, "dump expected: %d, dump saved: %d", dump, vm.dump);
	cr_expect_str_eq(vm.champ[1]->header.prog_name, player_1, "player_1 expected: %s, player_1 saved: %s", player_1, vm.champ[1]->header.prog_name);
	cr_expect_str_eq(vm.champ[2]->header.prog_name, player_2, "player_2 expected: %s, player_2 saved: %s", player_2, vm.champ[2]->header.prog_name);
	free_vm(&vm);
}

Test(input_validation, valid_n_option_four_players_2)
{
	int		expected_return = SUCCESS;
	int		given_argc = 13;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("-n");
	given_argv[2] = ft_strdup("4");
	given_argv[3] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/fluttershy.cor");
	given_argv[4] = ft_strdup("-n");
	given_argv[5] = ft_strdup("1");
	given_argv[6] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/helltrain.cor");
	given_argv[7] = ft_strdup("-n");
	given_argv[8] = ft_strdup("2");
	given_argv[9] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bigzork.cor");
	given_argv[10] = ft_strdup("-n");
	given_argv[11] = ft_strdup("3");
	given_argv[12] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bee_gees.cor");

	char	*player_1 = "helltrain";
	char	*player_2 = "bigzork";
	char	*player_3 = "stayin' alive";
	char	*player_4 = "fluttershy";

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "error when validation input");
	cr_expect_str_eq(vm.champ[1]->header.prog_name, player_1, "player_1 expected: %s, player_1 saved: %s", player_1, vm.champ[1]->header.prog_name);
	cr_expect_str_eq(vm.champ[2]->header.prog_name, player_2, "player_2 expected: %s, player_2 saved: %s", player_2, vm.champ[2]->header.prog_name);
	cr_expect_str_eq(vm.champ[3]->header.prog_name, player_3, "player_3 expected: %s, player_3 saved: %s", player_3, vm.champ[3]->header.prog_name);
	cr_expect_str_eq(vm.champ[4]->header.prog_name, player_4, "player_4 expected: %s, player_4 saved: %s", player_4, vm.champ[4]->header.prog_name);
	free_vm(&vm);
}

Test(input_validation, valid_n_option_four_players_1)
{
	int		expected_return = SUCCESS;
	int		given_argc = 7;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/turtle.cor");
	given_argv[2] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/zork.cor");
	given_argv[3] = ft_strdup("-n");
	given_argv[4] = ft_strdup("2");
	given_argv[5] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bigzork.cor");
	given_argv[6] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bee_gees.cor");

	char	*player_1 = "turtle";
	char	*player_2 = "bigzork";
	char	*player_3 = "zork";
	char	*player_4 = "stayin' alive";

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "error when validation input");
	cr_expect_str_eq(vm.champ[1]->header.prog_name, player_1, "player_1 expected: %s, player_1 saved: %s", player_1, vm.champ[1]->header.prog_name);
	cr_expect_str_eq(vm.champ[2]->header.prog_name, player_2, "player_2 expected: %s, player_2 saved: %s", player_2, vm.champ[2]->header.prog_name);
	cr_expect_str_eq(vm.champ[3]->header.prog_name, player_3, "player_3 expected: %s, player_3 saved: %s", player_3, vm.champ[3]->header.prog_name);
	cr_expect_str_eq(vm.champ[4]->header.prog_name, player_4, "player_4 expected: %s, player_4 saved: %s", player_4, vm.champ[4]->header.prog_name);
	free_vm(&vm);
}

Test(input_validation, valid_n_option_three_players_2)
{
	int		expected_return = SUCCESS;
	int		given_argc = 6;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/turtle.cor");
	given_argv[2] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/zork.cor");
	given_argv[3] = ft_strdup("-n");
	given_argv[4] = ft_strdup("3");
	given_argv[5] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bigzork.cor");

	char	*player_1 = "turtle";
	char	*player_2 = "zork";
	char	*player_3 = "bigzork";

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "error when validation input");
	cr_expect_str_eq(vm.champ[1]->header.prog_name, player_1, "player_1 expected: %s, player_1 saved: %s", player_1, vm.champ[1]->header.prog_name);
	cr_expect_str_eq(vm.champ[2]->header.prog_name, player_2, "player_2 expected: %s, player_2 saved: %s", player_2, vm.champ[2]->header.prog_name);
	cr_expect_str_eq(vm.champ[3]->header.prog_name, player_3, "player_3 expected: %s, player_3 saved: %s", player_3, vm.champ[3]->header.prog_name);
	free_vm(&vm);
}

Test(input_validation, valid_n_option_three_players_1)
{
	int		expected_return = SUCCESS;
	int		given_argc = 6;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/turtle.cor");
	given_argv[2] = ft_strdup("-n");
	given_argv[3] = ft_strdup("1");
	given_argv[4] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/zork.cor");
	given_argv[5] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bigzork.cor");

	char	*player_1 = "zork";
	char	*player_2 = "turtle";
	char	*player_3 = "bigzork";

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "error when validation input");
	cr_expect_str_eq(vm.champ[1]->header.prog_name, player_1, "player_1 expected: %s, player_1 saved: %s", player_1, vm.champ[1]->header.prog_name);
	cr_expect_str_eq(vm.champ[2]->header.prog_name, player_2, "player_2 expected: %s, player_2 saved: %s", player_2, vm.champ[2]->header.prog_name);
	cr_expect_str_eq(vm.champ[3]->header.prog_name, player_3, "player_3 expected: %s, player_3 saved: %s", player_3, vm.champ[3]->header.prog_name);
	free_vm(&vm);
}

Test(input_validation, valid_n_option_two_players)
{
	int		expected_return = SUCCESS;
	int		given_argc = 5;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("-n");
	given_argv[2] = ft_strdup("2");
	given_argv[3] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/zork.cor");
	given_argv[4] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bigzork.cor");

	char	*player_1 = "bigzork";
	char	*player_2 = "zork";

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "error when validation input");
	cr_expect_str_eq(vm.champ[1]->header.prog_name, player_1, "player_1 expected: %s, player_1 saved: %s", player_1, vm.champ[1]->header.prog_name);
	cr_expect_str_eq(vm.champ[2]->header.prog_name, player_2, "player_2 expected: %s, player_2 saved: %s", player_2, vm.champ[2]->header.prog_name);
	free_vm(&vm);
}

Test(input_validation, valid_four_players)
{
	int		expected_return = SUCCESS;
	int		given_argc = 5;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/zork.cor");
	given_argv[2] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/zork.cor");
	given_argv[3] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/zork.cor");
	given_argv[4] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/zork.cor");

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "with four valid champions given, input validation returned %d when the expected return is %d", expected_return, real_return);
	free_vm(&vm);
}

Test(input_validation, valid_three_players)
{
	int		expected_return = SUCCESS;
	int		given_argc = 4;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/turtle.cor");
	given_argv[2] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/fluttershy.cor");
	given_argv[3] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/zork.cor");

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "with three valid champions given, input validation returned %d when the expected return is %d", expected_return, real_return);
	cr_expect_str_eq(vm.champ[1]->header.prog_name, "turtle", "first champion should be turtle but is %s\n", vm.champ[1]->header.prog_name);
	cr_expect_str_eq(vm.champ[2]->header.prog_name, "fluttershy", "second champion should be fluttershy but is %s\n", vm.champ[2]->header.prog_name);
	cr_expect_str_eq(vm.champ[3]->header.prog_name, "zork", "third champion should be zork but is %s\n", vm.champ[3]->header.prog_name);

	cr_expect_str_eq(vm.champ[1]->header.comment, "TURTLE FFS U LAMA", "comment of turtle should be | TURTLE FFS U LAMA | but is | %s | \n", vm.champ[1]->header.comment);
	cr_expect_str_eq(vm.champ[2]->header.comment, "oh, my, what a scary project", "comment of fluttershy should be | oh, my, what a scary project | but is | %s | \n", vm.champ[2]->header.comment);
	cr_expect_str_eq(vm.champ[3]->header.comment, "I'M ALIIIIVE", "comment of zork should be | I’M ALIIIIVE | but is | %s | \n", vm.champ[3]->header.comment);

	cr_expect_eq(vm.champ[1]->header.prog_size, 394, "turtle should be 394 bytes heavy, not %d", vm.champ[1]->header.prog_size);
	cr_expect_eq(vm.champ[2]->header.prog_size, 490, "fluttershy should be 490 bytes heavy, not %d", vm.champ[2]->header.prog_size);
	cr_expect_eq(vm.champ[3]->header.prog_size, 24, "zork should be 24 bytes heavy, not %d", vm.champ[3]->header.prog_size);
	free_vm(&vm);
}

Test(input_validation, valid_two_players)
{
	int		expected_return = SUCCESS;
	int		given_argc = 3;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bee_gees.cor");
	given_argv[2] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/helltrain.cor");

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "with two valid champions given, input validation returned %d when the expected return is %d", expected_return, real_return);
	free_vm(&vm);
}

Test(input_validation, valid_one_players)
{
	int		expected_return = SUCCESS;
	int		given_argc = 2;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("test_folder/vm_test_folder/valid_cor_files/bigzork.cor");

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "with one valid champion given, input validation returned %d when the expected return is %d", expected_return, real_return);
	cr_expect_str_eq(vm.champ[1]->header.prog_name, "bigzork", "first champion should be bigzork but is %s\n", vm.champ[1]->header.prog_name);
	cr_expect_str_eq(vm.champ[1]->header.comment, "I know i cant win", "comment of bigzork should be | I know i cant win | but is | %s | \n", vm.champ[1]->header.comment);
	cr_expect_eq(vm.champ[1]->header.prog_size, 430, "bigzork should be 430 bytes heavy, not %d", vm.champ[1]->header.prog_size);
	free_vm(&vm);
}

Test(input_validation, no_args, .init=redirect_all_stdout)
{
	int		expected_return = SUCCESS;
	int		given_argc = 1;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);

	given_argv[0] = ft_strdup("corewar");

	t_vm	vm;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "with no arguments given, input validation returned %d when the expected return is %d", expected_return, real_return);
	free_vm(&vm);
}
