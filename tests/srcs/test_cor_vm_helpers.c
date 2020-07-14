#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "corewar.h"

Test(new_idx, neg_6)
{
	unsigned int	current_idx = 2;
	int				offset = -12291;
	unsigned int	l_flag = TRUE;
	unsigned int	expected_new = 4095;

	unsigned int	calculated_idx = new_idx(current_idx, offset, l_flag);
	cr_assert_eq(calculated_idx, expected_new, "current_idx = %d, offset = %d, l_flag = %d\nnew_idx = %d is incorrect\n", current_idx, offset, l_flag, calculated_idx);
}

Test(new_idx, neg_5)
{
	unsigned int	current_idx = 2;
	int				offset = -3;
	unsigned int	l_flag = TRUE;
	unsigned int	expected_new = 4095;

	unsigned int	calculated_idx = new_idx(current_idx, offset, l_flag);
	cr_assert_eq(calculated_idx, expected_new, "current_idx = %d, offset = %d, l_flag = %d\nnew_idx = %d is incorrect\n", current_idx, offset, l_flag, calculated_idx);
}

Test(new_idx, neg_4)
{
	unsigned int	current_idx = 2;
	int				offset = -1026;
	unsigned int	l_flag = TRUE;
	unsigned int	expected_new = 3072;

	unsigned int	calculated_idx = new_idx(current_idx, offset, l_flag);
	cr_assert_eq(calculated_idx, expected_new, "current_idx = %d, offset = %d, l_flag = %d\nnew_idx = %d is incorrect\n", current_idx, offset, l_flag, calculated_idx);
}

Test(new_idx, neg_3)
{
	unsigned int	current_idx = 2;
	int				offset = -1026;
	unsigned int	l_flag = FALSE;
	unsigned int	expected_new = 0;

	unsigned int	calculated_idx = new_idx(current_idx, offset, l_flag);
	cr_assert_eq(calculated_idx, expected_new, "current_idx = %d, offset = %d, l_flag = %d\nnew_idx = %d is incorrect\n", current_idx, offset, l_flag, calculated_idx);
}

Test(new_idx, neg_2)
{
	unsigned int	current_idx = 312;
	int				offset = -200;
	unsigned int	l_flag = TRUE;
	unsigned int	expected_new = 112;

	unsigned int	calculated_idx = new_idx(current_idx, offset, l_flag);
	cr_assert_eq(calculated_idx, expected_new, "current_idx = %d, offset = %d, l_flag = %d\nnew_idx = %d is incorrect\n", current_idx, offset, l_flag, calculated_idx);
}

Test(new_idx, neg_1)
{
	unsigned int	current_idx = 312;
	int				offset = -400;
	unsigned int	l_flag = TRUE;
	unsigned int	expected_new = 4008;

	unsigned int	calculated_idx = new_idx(current_idx, offset, l_flag);
	cr_assert_eq(calculated_idx, expected_new, "current_idx = %d, offset = %d, l_flag = %d\nnew_idx = %d is incorrect\n", current_idx, offset, l_flag, calculated_idx);
}

Test(new_idx, pos_9)
{
	unsigned int	current_idx = MEM_SIZE;
	int				offset = 42;
	unsigned int	l_flag = TRUE;
	unsigned int	expected_new = 42;

	unsigned int	calculated_idx = new_idx(current_idx, offset, l_flag);
	cr_assert_eq(calculated_idx, expected_new, "current_idx = %d, offset = %d, l_flag = %d\nnew_idx = %d is incorrect\n", current_idx, offset, l_flag, calculated_idx);
}

Test(new_idx, pos_8)
{
	unsigned int	current_idx = MEM_SIZE - 1;
	int				offset = 1;
	unsigned int	l_flag = TRUE;
	unsigned int	expected_new = 0;

	unsigned int	calculated_idx = new_idx(current_idx, offset, l_flag);
	cr_assert_eq(calculated_idx, expected_new, "current_idx = %d, offset = %d, l_flag = %d\nnew_idx = %d is incorrect\n", current_idx, offset, l_flag, calculated_idx);
}

Test(new_idx, pos_7)
{
	unsigned int	current_idx = 3696;
	int				offset = 913;
	unsigned int	l_flag = TRUE;
	unsigned int	expected_new = 513;

	unsigned int	calculated_idx = new_idx(current_idx, offset, l_flag);
	cr_assert_eq(calculated_idx, expected_new, "current_idx = %d, offset = %d, l_flag = %d\nnew_idx = %d is incorrect\n", current_idx, offset, l_flag, calculated_idx);
}

Test(new_idx, pos_6)
{
	unsigned int	current_idx = 3696;
	int				offset = 913;
	unsigned int	l_flag = FALSE;
	unsigned int	expected_new = 1;

	unsigned int	calculated_idx = new_idx(current_idx, offset, l_flag);
	cr_assert_eq(calculated_idx, expected_new, "current_idx = %d, offset = %d, l_flag = %d\nnew_idx = %d is incorrect\n", current_idx, offset, l_flag, calculated_idx);
}

Test(new_idx, pos_5)
{
	unsigned int	current_idx = 4000;
	int				offset = 100;
	unsigned int	l_flag = TRUE;
	unsigned int	expected_new = 4;

	unsigned int	calculated_idx = new_idx(current_idx, offset, l_flag);
	cr_assert_eq(calculated_idx, expected_new, "current_idx = %d, offset = %d, l_flag = %d\nnew_idx = %d is incorrect\n", current_idx, offset, l_flag, calculated_idx);
}

Test(new_idx, pos_4)
{
	unsigned int	current_idx = 2096;
	int				offset = 3046;
	unsigned int	l_flag = TRUE;
	unsigned int	expected_new = 1046;

	unsigned int	calculated_idx = new_idx(current_idx, offset, l_flag);
	cr_assert_eq(calculated_idx, expected_new, "current_idx = %d, offset = %d, l_flag = %d\nnew_idx = %d is incorrect\n", current_idx, offset, l_flag, calculated_idx);
}

Test(new_idx, pos_3)
{
	unsigned int	current_idx = 2096;
	int				offset = 3046;
	unsigned int	l_flag = FALSE;
	unsigned int	expected_new = 2582;

	unsigned int	calculated_idx = new_idx(current_idx, offset, l_flag);
	cr_assert_eq(calculated_idx, expected_new, "current_idx = %d, offset = %d, l_flag = %d\nnew_idx = %d is incorrect\n", current_idx, offset, l_flag, calculated_idx);
}

Test(new_idx, pos_2)
{
	unsigned int	current_idx = 4095;
	int				offset = 1;
	unsigned int	l_flag = FALSE;
	unsigned int	expected_new = 0;

	unsigned int	calculated_idx = new_idx(current_idx, offset, l_flag);
	cr_assert_eq(calculated_idx, expected_new, "current_idx = %d, offset = %d, l_flag = %d\nnew_idx = %d is incorrect\n", current_idx, offset, l_flag, calculated_idx);
}

Test(new_idx, pos_1)
{
	unsigned int	current_idx = 2738;
	int				offset = 46;
	unsigned int	l_flag = FALSE;
	unsigned int	expected_new = 2784;

	unsigned int	calculated_idx = new_idx(current_idx, offset, l_flag);
	cr_assert_eq(calculated_idx, expected_new, "current_idx = %d, offset = %d, l_flag = %d\nnew_idx = %d is incorrect\n", current_idx, offset, l_flag, calculated_idx);
}


///////////////////////////////////////////////////////////////////////////////
//	CONVERSION	CONVERSION	CONVERSION	CONVERSION	CONVERSION	CONVERSION	 //
///////////////////////////////////////////////////////////////////////////////


Test(convert_to_int, 4_valid_neg)
{
	unsigned char	buf[MEM_SIZE];
	ft_bzero(buf, MEM_SIZE);
	int expected_int = -253066253;
	unsigned int len = 4;
	unsigned int start_idx = MEM_SIZE - 1;

	unsigned int i = len;
	while (i > 0)
	{
		buf[new_idx(start_idx, i - 1, TRUE)] = ((unsigned char*)&expected_int)[len - i];
		--i;
	}
	int return_int = convert_to_int(buf, start_idx, len);
	cr_assert_eq(return_int, expected_int, "expected value = %d doesn't match return value = %d", expected_int, return_int);
}

Test(convert_to_int, 4_valid_zero)
{
	unsigned char	buf[MEM_SIZE];
	ft_bzero(buf, MEM_SIZE);
	int expected_int = 0;
	unsigned int len = 4;
	unsigned int start_idx = MEM_SIZE - 4;

	unsigned int i = len;
	while (i > 0)
	{
		buf[new_idx(start_idx, i - 1, TRUE)] = ((unsigned char*)&expected_int)[len - i];
		--i;
	}
	int return_int = convert_to_int(buf, start_idx, len);
	cr_assert_eq(return_int, expected_int, "expected value = %d doesn't match return value = %d", expected_int, return_int);
}

Test(convert_to_int, 4_valid_one)
{
	unsigned char	buf[MEM_SIZE];
	ft_bzero(buf, MEM_SIZE);
	int expected_int = 1;
	unsigned int len = 4;
	unsigned int start_idx = MEM_SIZE - 2;

	unsigned int i = len;
	while (i > 0)
	{
		buf[new_idx(start_idx, i - 1, TRUE)] = ((unsigned char*)&expected_int)[len - i];
		--i;
	}
	int return_int = convert_to_int(buf, start_idx, len);
	cr_assert_eq(return_int, expected_int, "expected value = %d doesn't match return value = %d", expected_int, return_int);
}

Test(convert_to_int, 4_valid_magic)
{
	unsigned char	buf[MEM_SIZE];
	ft_bzero(buf, MEM_SIZE);
	int expected_int = 15369203;
	unsigned int len = 4;
	unsigned int start_idx = new_idx(MEM_SIZE - 1, 4, TRUE);

	unsigned int i = len;
	while (i > 0)
	{
		buf[new_idx(start_idx, i - 1, TRUE)] = ((unsigned char*)&expected_int)[len - i];
		--i;
	}
	int return_int = convert_to_int(buf, start_idx, len);
	cr_assert_eq(return_int, expected_int, "expected value = %d doesn't match return value = %d", expected_int, return_int);
}


Test(convert_to_int, 3_valid_zero)
{
	unsigned char	buf[MEM_SIZE];
	ft_bzero(buf, MEM_SIZE);
	int expected_int = 0;
	unsigned int len = 3;
	unsigned int start_idx = new_idx(MEM_SIZE - 1, 1, TRUE);

	unsigned int i = len;
	while (i > 0)
	{
		buf[new_idx(start_idx, i - 1, TRUE)] = ((unsigned char*)&expected_int)[len - i];
		--i;
	}
	int return_int = convert_to_int(buf, start_idx, len);
	cr_assert_eq(return_int, expected_int, "expected value = %d doesn't match return value = %d", expected_int, return_int);
}

Test(convert_to_int, 3_valid_one)
{
	unsigned char	buf[MEM_SIZE];
	ft_bzero(buf, MEM_SIZE);
	int expected_int = 1;
	unsigned int len = 3;
	unsigned int start_idx = new_idx(MEM_SIZE - 1, 1, TRUE);

	unsigned int i = len;
	while (i > 0)
	{
		buf[new_idx(start_idx, i - 1, TRUE)] = ((unsigned char*)&expected_int)[len - i];
		--i;
	}
	int return_int = convert_to_int(buf, start_idx, len);
	cr_assert_eq(return_int, expected_int, "expected value = %d doesn't match return value = %d", expected_int, return_int);
}

Test(convert_to_int, 3_valid_magic)
{
	unsigned char	buf[MEM_SIZE];
	ft_bzero(buf, MEM_SIZE);
	int expected_int = 15369203;
	unsigned int len = 3;
	unsigned int start_idx = new_idx(MEM_SIZE - 1, 4, TRUE);

	unsigned int i = len;
	while (i > 0)
	{
		buf[new_idx(start_idx, i - 1, TRUE)] = ((unsigned char*)&expected_int)[len - i];
		--i;
	}
	int return_int = convert_to_int(buf, start_idx, len);
	cr_assert_eq(return_int, expected_int, "expected value = %d doesn't match return value = %d", expected_int, return_int);
}

Test(convert_to_int, 2_valid_zero)
{
	unsigned char	buf[MEM_SIZE];
	ft_bzero(buf, MEM_SIZE);
	int expected_int = 0;
	unsigned int len = 2;
	unsigned int start_idx = new_idx(MEM_SIZE - 1, 1, TRUE);

	unsigned int i = len;
	while (i > 0)
	{
		buf[new_idx(start_idx, i - 1, TRUE)] = ((unsigned char*)&expected_int)[len - i];
		--i;
	}
	int return_int = convert_to_int(buf, start_idx, len);
	cr_assert_eq(return_int, expected_int, "expected value = %d doesn't match return value = %d", expected_int, return_int);
}

Test(convert_to_int, 2_valid_one)
{
	unsigned char	buf[MEM_SIZE];
	ft_bzero(buf, MEM_SIZE);
	int expected_int = 1;
	unsigned int len = 2;
	unsigned int start_idx = new_idx(MEM_SIZE - 1, 4, TRUE);

	unsigned int i = len;
	while (i > 0)
	{
		buf[new_idx(start_idx, i - 1, TRUE)] = ((unsigned char*)&expected_int)[len - i];
		--i;
	}
	int return_int = convert_to_int(buf, start_idx, len);
	cr_assert_eq(return_int, expected_int, "expected value = %d doesn't match return value = %d", expected_int, return_int);
}

Test(convert_to_int, 2_valid_magic)
{
	unsigned char	buf[MEM_SIZE];
	ft_bzero(buf, MEM_SIZE);
	int expected_int = 33779;
	unsigned int len = 2;
	unsigned int start_idx = new_idx(MEM_SIZE - 1, 4, TRUE);

	unsigned int i = len;
	while (i > 0)
	{
		buf[new_idx(start_idx, i - 1, TRUE)] = ((unsigned char*)&expected_int)[len - i];
		--i;
	}
	int return_int = convert_to_int(buf, start_idx, len);
	cr_assert_eq(return_int, expected_int, "expected value = %d doesn't match return value = %d", expected_int, return_int);
}

Test(convert_to_int, 1_valid_zero)
{
	unsigned char	buf[MEM_SIZE];
	ft_bzero(buf, MEM_SIZE);
	int expected_int = 0;
	unsigned int len = 1;
	unsigned int start_idx = new_idx(MEM_SIZE - 1, 1, TRUE);

	unsigned int i = len;
	while (i > 0)
	{
		buf[new_idx(start_idx, i - 1, TRUE)] = ((unsigned char*)&expected_int)[len - i];
		--i;
	}
	int return_int = convert_to_int(buf, start_idx, len);
	cr_assert_eq(return_int, expected_int, "expected value = %d doesn't match return value = %d", expected_int, return_int);
}

Test(convert_to_int, 1_valid_one)
{
	unsigned char	buf[MEM_SIZE];
	ft_bzero(buf, MEM_SIZE);
	int expected_int = 1;
	unsigned int len = 1;
	unsigned int start_idx = new_idx(MEM_SIZE - 1, 7, TRUE);

	unsigned int i = len;
	while (i > 0)
	{
		buf[new_idx(start_idx, i - 1, TRUE)] = ((unsigned char*)&expected_int)[len - i];
		--i;
	}
	int return_int = convert_to_int(buf, start_idx, len);
	cr_assert_eq(return_int, expected_int, "expected value = %d doesn't match return value = %d", expected_int, return_int);
}

Test(convert_to_int, 1_valid_magic)
{
	unsigned char	buf[MEM_SIZE];
	ft_bzero(buf, MEM_SIZE);
	int expected_int = 131;
	unsigned int len = 1;
	unsigned int start_idx = new_idx(MEM_SIZE - 1, 6, TRUE);

	unsigned int i = len;
	while (i > 0)
	{
		buf[new_idx(start_idx, i - 1, TRUE)] = ((unsigned char*)&expected_int)[len - i];
		--i;
	}
	int return_int = convert_to_int(buf, start_idx, len);
	cr_assert_eq(return_int, expected_int, "expected value = %d doesn't match return value = %d", expected_int, return_int);
}
