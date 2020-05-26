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
	unsigned char	buf[10];
	int				return_int;
	int				expected_int;

	ft_bzero(buf, 10);
	expected_int = 1;
	buf[6] = 1;
	return_int = convert_to_int(buf + 3);
	cr_assert_eq(return_int, expected_int, "expected value = %d doesn't match return value = %d", expected_int, return_int);
}
