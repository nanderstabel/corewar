#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "corewar.h"

void	redirect_all_stdout(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

///////////////////////////////////////////////////////////////////////////////
//	INVALID		INVALID		INVALID		INVALID		INVALID		INVALID		 //
///////////////////////////////////////////////////////////////////////////////

Test(input_validation, invalid_five_players, .init=redirect_all_stdout)
{
	int		expected_return = ERROR;
	int		expected_output_fd = STDERR;
	char	*expected_output = TOO_MANY_CHAMPS;

	int		given_argc = 6;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("tests/testfiles/valid/zork.cor");
	given_argv[2] = ft_strdup("tests/testfiles/valid/bigzork.cor");
	given_argv[3] = ft_strdup("tests/testfiles/valid/fluttershy.cor");
	given_argv[4] = ft_strdup("tests/testfiles/valid/bee_gees.cor");
	given_argv[5] = ft_strdup("tests/testfiles/valid/turtle.cor");

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "with four valid champions given, input validation returned %d when the expected return is %d", expected_return, real_return);

	if (expected_output_fd == STDOUT)
		cr_assert_stdout_eq_str(expected_output, "");
	if (expected_output_fd == STDERR)
		cr_assert_stderr_eq_str(expected_output, "");
}


///////////////////////////////////////////////////////////////////////////////
//		VALID		VALID		VALID		VALID		VALID		VALID	 //
///////////////////////////////////////////////////////////////////////////////


Test(input_validation, valid_n_option_two_players)
{
	int		expected_return = SUCCESS;
	int		given_argc = 5;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("-n");
	given_argv[2] = ft_strdup("2");
	given_argv[3] = ft_strdup("tests/testfiles/valid/zork.cor");
	given_argv[4] = ft_strdup("tests/testfiles/valid/bigzork.cor");

	char	*player_1 = "bigzork";
	char	*player_2 = "zork";

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "error when validation input", expected_return, real_return);
	cr_expect_str_eq(vm.champions[1]->prog_name, player_1, "player_1 expected: %s, player_1 saved: %s", player_1, vm.champions[1]);
	cr_expect_str_eq(vm.champions[2]->prog_name, player_2, "player_2 expected: %s, player_2 saved: %s", player_2, vm.champions[2]);
}

Test(input_validation, valid_four_players)
{
	int		expected_return = SUCCESS;
	int		given_argc = 5;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("tests/testfiles/valid/zork.cor");
	given_argv[2] = ft_strdup("tests/testfiles/valid/zork.cor");
	given_argv[3] = ft_strdup("tests/testfiles/valid/zork.cor");
	given_argv[4] = ft_strdup("tests/testfiles/valid/zork.cor");

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "with four valid champions given, input validation returned %d when the expected return is %d", expected_return, real_return);
}

Test(input_validation, valid_three_players)
{
	int		expected_return = SUCCESS;
	int		given_argc = 4;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("tests/testfiles/valid/turtle.cor");
	given_argv[2] = ft_strdup("tests/testfiles/valid/fluttershy.cor");
	given_argv[3] = ft_strdup("tests/testfiles/valid/zork.cor");

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "with three valid champions given, input validation returned %d when the expected return is %d", expected_return, real_return);
}

Test(input_validation, valid_two_players)
{
	int		expected_return = SUCCESS;
	int		given_argc = 3;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("tests/testfiles/valid/bee_gees.cor");
	given_argv[2] = ft_strdup("tests/testfiles/valid/helltrain.cor");

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "with two valid champions given, input validation returned %d when the expected return is %d", expected_return, real_return);
}

Test(input_validation, valid_one_players)
{
	int		expected_return = SUCCESS;
	int		given_argc = 2;
	char	**given_argv = (char**)ft_memalloc(sizeof(char*) * given_argc);

	given_argv[0] = ft_strdup("corewar");
	given_argv[1] = ft_strdup("tests/testfiles/valid/bigzork.cor");

	t_vm	vm;
	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = -1;
	int		real_return = input_validation(&vm, given_argv, given_argc);
	cr_assert_eq(real_return, expected_return, "with one valid champion given, input validation returned %d when the expected return is %d", expected_return, real_return);
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
}
