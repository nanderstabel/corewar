#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "corewar.h"

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
