#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "corewar.h"


///////////////////////////////////////////////////////////////////////////////
//	CONVERSION	CONVERSION	CONVERSION	CONVERSION	CONVERSION	CONVERSION	 //
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
