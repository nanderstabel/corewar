/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_cor_op_helpers.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 12:09:44 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/14 12:09:44 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "corewar.h"

Test(get_arg_type, mix_3)
{
	unsigned char	enc = 96;	// 01 10 00 00
	int				type_1 = REG;
	int				type_2 = DIR;
	int				type_3 = 0;
	int				type_4 = 0;

	int	return_1 = get_arg_type(enc, 1);
	int	return_2 = get_arg_type(enc, 2);
	int	return_3 = get_arg_type(enc, 3);
	int	return_4 = get_arg_type(enc, 4);
	cr_expect_eq(return_1, type_1, "return for arg_1: %d, expected: %d\n", return_1, type_1);
	cr_expect_eq(return_2, type_2, "return for arg_2: %d, expected: %d\n", return_2, type_2);
	cr_expect_eq(return_3, type_3, "return for arg_3: %d, expected: %d\n", return_3, type_3);
	cr_expect_eq(return_4, type_4, "return for arg_4: %d, expected: %d\n", return_4, type_4);
}

Test(get_arg_type, mix_2)
{
	unsigned char	enc = 216;	// 11 01 10 00
	int				type_1 = IND;
	int				type_2 = REG;
	int				type_3 = DIR;
	int				type_4 = 0;

	int	return_1 = get_arg_type(enc, 1);
	int	return_2 = get_arg_type(enc, 2);
	int	return_3 = get_arg_type(enc, 3);
	int	return_4 = get_arg_type(enc, 4);
	cr_expect_eq(return_1, type_1, "return for arg_1: %d, expected: %d\n", return_1, type_1);
	cr_expect_eq(return_2, type_2, "return for arg_2: %d, expected: %d\n", return_2, type_2);
	cr_expect_eq(return_3, type_3, "return for arg_3: %d, expected: %d\n", return_3, type_3);
	cr_expect_eq(return_4, type_4, "return for arg_4: %d, expected: %d\n", return_4, type_4);
}

Test(get_arg_type, mix_1)
{
	unsigned char	enc = 120;	// 01 11 10 00
	int				type_1 = REG;
	int				type_2 = IND;
	int				type_3 = DIR;
	int				type_4 = 0;

	int	return_1 = get_arg_type(enc, 1);
	int	return_2 = get_arg_type(enc, 2);
	int	return_3 = get_arg_type(enc, 3);
	int	return_4 = get_arg_type(enc, 4);
	cr_expect_eq(return_1, type_1, "return for arg_1: %d, expected: %d\n", return_1, type_1);
	cr_expect_eq(return_2, type_2, "return for arg_2: %d, expected: %d\n", return_2, type_2);
	cr_expect_eq(return_3, type_3, "return for arg_3: %d, expected: %d\n", return_3, type_3);
	cr_expect_eq(return_4, type_4, "return for arg_4: %d, expected: %d\n", return_4, type_4);
}

Test(get_arg_type, ind)
{
	unsigned char	enc = 255;	// 11 11 11 11
	int				type_1 = IND;
	int				type_2 = IND;
	int				type_3 = IND;
	int				type_4 = IND;

	int	return_1 = get_arg_type(enc, 1);
	int	return_2 = get_arg_type(enc, 2);
	int	return_3 = get_arg_type(enc, 3);
	int	return_4 = get_arg_type(enc, 4);
	cr_expect_eq(return_1, type_1, "return for arg_1: %d, expected: %d\n", return_1, type_1);
	cr_expect_eq(return_2, type_2, "return for arg_2: %d, expected: %d\n", return_2, type_2);
	cr_expect_eq(return_3, type_3, "return for arg_3: %d, expected: %d\n", return_3, type_3);
	cr_expect_eq(return_4, type_4, "return for arg_4: %d, expected: %d\n", return_4, type_4);
}

Test(get_arg_type, dir)
{
	unsigned char	enc = 170;	// 10 10 10 10
	int				type_1 = DIR;
	int				type_2 = DIR;
	int				type_3 = DIR;
	int				type_4 = DIR;

	int	return_1 = get_arg_type(enc, 1);
	int	return_2 = get_arg_type(enc, 2);
	int	return_3 = get_arg_type(enc, 3);
	int	return_4 = get_arg_type(enc, 4);
	cr_expect_eq(return_1, type_1, "return for arg_1: %d, expected: %d\n", return_1, type_1);
	cr_expect_eq(return_2, type_2, "return for arg_2: %d, expected: %d\n", return_2, type_2);
	cr_expect_eq(return_3, type_3, "return for arg_3: %d, expected: %d\n", return_3, type_3);
	cr_expect_eq(return_4, type_4, "return for arg_4: %d, expected: %d\n", return_4, type_4);
}

Test(get_arg_type, reg)
{
	unsigned char	enc = 85;	// 01 01 01 01
	int				type_1 = REG;
	int				type_2 = REG;
	int				type_3 = REG;
	int				type_4 = REG;

	int	return_1 = get_arg_type(enc, 1);
	int	return_2 = get_arg_type(enc, 2);
	int	return_3 = get_arg_type(enc, 3);
	int	return_4 = get_arg_type(enc, 4);
	cr_expect_eq(return_1, type_1, "return for arg_1: %d, expected: %d\n", return_1, type_1);
	cr_expect_eq(return_2, type_2, "return for arg_2: %d, expected: %d\n", return_2, type_2);
	cr_expect_eq(return_3, type_3, "return for arg_3: %d, expected: %d\n", return_3, type_3);
	cr_expect_eq(return_4, type_4, "return for arg_4: %d, expected: %d\n", return_4, type_4);
}

Test(get_arg_type, zero)
{
	unsigned char	enc = 0;
	int				type_1 = 0;
	int				type_2 = 0;
	int				type_3 = 0;
	int				type_4 = 0;

	int	return_1 = get_arg_type(enc, 1);
	int	return_2 = get_arg_type(enc, 2);
	int	return_3 = get_arg_type(enc, 3);
	int	return_4 = get_arg_type(enc, 4);
	cr_expect_eq(return_1, type_1, "return for arg_1: %d, expected: %d\n", return_1, type_1);
	cr_expect_eq(return_2, type_2, "return for arg_2: %d, expected: %d\n", return_2, type_2);
	cr_expect_eq(return_3, type_3, "return for arg_3: %d, expected: %d\n", return_3, type_3);
	cr_expect_eq(return_4, type_4, "return for arg_4: %d, expected: %d\n", return_4, type_4);
}
