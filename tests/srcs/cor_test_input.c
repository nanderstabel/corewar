#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "corewar.h"
#include "libft.h"

void	redirect_all_stdout(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

Test(input_validation, valid_four, .init=redirect_all_stdout)
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

// uncomment the following for checking the output for invalid input:

	// char	*expected_output = USAGE;
	// int		expected_output_fd = STDOUT;

	// if (expected_output_fd == STDOUT)
	// 	cr_assert_stdout_eq_str(expected_output, "");
	// if (expected_output_fd == STDERR)
	// 	cr_assert_stderr_eq_str(expected_output, "");
}

Test(input_validation, valid_three, .init=redirect_all_stdout)
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

// uncomment the following for checking the output for invalid input:

	// char	*expected_output = USAGE;
	// int		expected_output_fd = STDOUT;

	// if (expected_output_fd == STDOUT)
	// 	cr_assert_stdout_eq_str(expected_output, "");
	// if (expected_output_fd == STDERR)
	// 	cr_assert_stderr_eq_str(expected_output, "");
}

Test(input_validation, valid_two, .init=redirect_all_stdout)
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

// uncomment the following for checking the output for invalid input:

	// char	*expected_output = USAGE;
	// int		expected_output_fd = STDOUT;

	// if (expected_output_fd == STDOUT)
	// 	cr_assert_stdout_eq_str(expected_output, "");
	// if (expected_output_fd == STDERR)
	// 	cr_assert_stderr_eq_str(expected_output, "");
}

Test(input_validation, valid_one, .init=redirect_all_stdout)
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

// uncomment the following for checking the output for invalid input:

	// char	*expected_output = USAGE;
	// int		expected_output_fd = STDOUT;

	// if (expected_output_fd == STDOUT)
	// 	cr_assert_stdout_eq_str(expected_output, "");
	// if (expected_output_fd == STDERR)
	// 	cr_assert_stderr_eq_str(expected_output, "");
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

// uncomment and edit the following for checking the output for invalid input:

	// char	*expected_output = USAGE;
	// int		expected_output_fd = STDOUT;

	// if (expected_output_fd == STDOUT)
	// 	cr_assert_stdout_eq_str(expected_output, "");
	// if (expected_output_fd == STDERR)
	// 	cr_assert_stderr_eq_str(expected_output, "");
}

///////////////////////////////////////////////////////////////////////////////

Test(convert_to_int, valid_zero)
{
	char	buf[10];
	int		return_int;
	int		expected_int;

	ft_bzero(buf, 10);
	expected_int = 0;
	return_int = convert_to_int(buf);
	cr_assert_eq(return_int, expected_int, "expected value = %d doesn't match return value = %d", expected_int, return_int);
}

Test(convert_to_int, valid_one)
{
	char	buf[10];
	int		return_int;
	int		expected_int;

	ft_bzero(buf, 10);
	expected_int = 1;
	buf[6] = 1;
	return_int = convert_to_int(buf + 3);
	cr_assert_eq(return_int, expected_int, "expected value = %d doesn't match return value = %d", expected_int, return_int);
}

Test(convert_to_int, valid_magic)
{
	char	buf[10];
	int		return_int;
	int		expected_int;

	ft_bzero(buf, 10);
	expected_int = 15369203;
	buf[6] = 0xf3;
	buf[5] = 0x83;
	buf[4] = 0xea;
	return_int = convert_to_int(buf + 3);
	cr_assert_eq(return_int, expected_int, "expected value = %d doesn't match return value = %d", expected_int, return_int);
}
