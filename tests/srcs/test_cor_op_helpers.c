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

Test(store_in_arena, len_4_neg)
{
	unsigned int	len = 4;
	int				value = -1;
	unsigned int	start_idx = MEM_SIZE - 2;

	unsigned char	arena[MEM_SIZE];
	ft_bzero(&arena, MEM_SIZE);
	store_in_arena(arena, start_idx, len, value);
	int converted = convert_to_int(arena, start_idx, len);
	cr_expect_eq(value, converted, "value = %d, converted from arena = %d\n", value, converted);
	unsigned int i = 0;
	unsigned char stored_byte;
	unsigned char value_byte;
	while (i < len)
	{
		stored_byte = arena[new_idx(start_idx, i, FALSE)];
		value_byte = ((unsigned char*)&value)[len - 1 - i];
		cr_expect_eq(stored_byte, value_byte, "stored_byte[%d]: %d, expected: %d\n", i, stored_byte, value_byte);
		++i;
	}
}

Test(store_in_arena, len_4_pos)
{
	unsigned int	len = 4;
	int				value = 42;
	unsigned int	start_idx = 42;

	unsigned char	arena[MEM_SIZE];
	ft_bzero(&arena, MEM_SIZE);
	store_in_arena(arena, start_idx, len, value);
	int converted = convert_to_int(arena, start_idx, len);
	cr_expect_eq(value, converted, "value = %d, converted from arena = %d\n", value, converted);
	unsigned int i = 0;
	unsigned char stored_byte;
	unsigned char value_byte;
	while (i < len)
	{
		stored_byte = arena[new_idx(start_idx, i, FALSE)];
		value_byte = ((unsigned char*)&value)[len - 1 - i];
		cr_expect_eq(stored_byte, value_byte, "stored_byte[%d]: %d, expected: %d\n", i, stored_byte, value_byte);
		++i;
	}
}

Test(store_in_arena, len_4_one)
{
	unsigned int	len = 4;
	int				value = 1;
	unsigned int	start_idx = 0;

	unsigned char	arena[MEM_SIZE];
	ft_bzero(&arena, MEM_SIZE);
	store_in_arena(arena, start_idx, len, value);
	int converted = convert_to_int(arena, start_idx, len);
	cr_expect_eq(value, converted, "value = %d, converted from arena = %d\n", value, converted);
	unsigned int i = 0;
	unsigned char stored_byte;
	unsigned char value_byte;
	while (i < len)
	{
		stored_byte = arena[new_idx(start_idx, i, FALSE)];
		value_byte = ((unsigned char*)&value)[len - 1 - i];
		cr_expect_eq(stored_byte, value_byte, "stored_byte[%d]: %d, expected: %d\n", i, stored_byte, value_byte);
		++i;
	}
}

Test(store_in_arena, len_4_zero)
{
	unsigned int	len = 4;
	int				value = 0;
	unsigned int	start_idx = MEM_SIZE / 5;

	unsigned char	arena[MEM_SIZE];
	ft_bzero(&arena, MEM_SIZE);
	store_in_arena(arena, start_idx, len, value);
	int converted = convert_to_int(arena, start_idx, len);
	cr_expect_eq(value, converted, "value = %d, converted from arena = %d\n", value, converted);
	unsigned int i = 0;
	unsigned char stored_byte;
	unsigned char value_byte;
	while (i < len)
	{
		stored_byte = arena[new_idx(start_idx, i, FALSE)];
		value_byte = ((unsigned char*)&value)[len - 1 - i];
		cr_expect_eq(stored_byte, value_byte, "stored_byte[%d]: %d, expected: %d\n", i, stored_byte, value_byte);
		++i;
	}
}



Test(store_in_arena, len_3_neg)
{
	unsigned int	len = 3;
	int				value = -978016;
	unsigned int	start_idx = MEM_SIZE - 6;

	unsigned char	arena[MEM_SIZE];
	ft_bzero(&arena, MEM_SIZE);
	store_in_arena(arena, start_idx, len, value);
	// int converted = convert_to_int(arena, start_idx, len);
	// cr_expect_eq(value, converted, "value = %d, converted from arena = %d\n", value, converted);
	unsigned int i = 0;
	unsigned char stored_byte;
	unsigned char value_byte;
	while (i < len)
	{
		stored_byte = arena[new_idx(start_idx, i, FALSE)];
		value_byte = ((unsigned char*)&value)[len - 1 - i];
		cr_expect_eq(stored_byte, value_byte, "stored_byte[%d]: %d, expected: %d\n", i, stored_byte, value_byte);
		++i;
	}
}

Test(store_in_arena, len_3_pos)
{
	unsigned int	len = 3;
	int				value = 978016;
	unsigned int	start_idx = MEM_SIZE - 253;

	unsigned char	arena[MEM_SIZE];
	ft_bzero(&arena, MEM_SIZE);
	store_in_arena(arena, start_idx, len, value);
	int converted = convert_to_int(arena, start_idx, len);
	cr_expect_eq(value, converted, "value = %d, converted from arena = %d\n", value, converted);
	unsigned int i = 0;
	unsigned char stored_byte;
	unsigned char value_byte;
	while (i < len)
	{
		stored_byte = arena[new_idx(start_idx, i, FALSE)];
		value_byte = ((unsigned char*)&value)[len - 1 - i];
		cr_expect_eq(stored_byte, value_byte, "stored_byte[%d]: %d, expected: %d\n", i, stored_byte, value_byte);
		++i;
	}
}

Test(store_in_arena, len_3_one)
{
	unsigned int	len = 3;
	int				value = 1;
	unsigned int	start_idx = 0;

	unsigned char	arena[MEM_SIZE];
	ft_bzero(&arena, MEM_SIZE);
	store_in_arena(arena, start_idx, len, value);
	int converted = convert_to_int(arena, start_idx, len);
	cr_expect_eq(value, converted, "value = %d, converted from arena = %d\n", value, converted);
	unsigned int i = 0;
	unsigned char stored_byte;
	unsigned char value_byte;
	while (i < len)
	{
		stored_byte = arena[new_idx(start_idx, i, FALSE)];
		value_byte = ((unsigned char*)&value)[len - 1 - i];
		cr_expect_eq(stored_byte, value_byte, "stored_byte[%d]: %d, expected: %d\n", i, stored_byte, value_byte);
		++i;
	}
}

Test(store_in_arena, len_3_zero)
{
	unsigned int	len = 3;
	int				value = 0;
	unsigned int	start_idx = MEM_SIZE - 6;

	unsigned char	arena[MEM_SIZE];
	ft_bzero(&arena, MEM_SIZE);
	store_in_arena(arena, start_idx, len, value);
	int converted = convert_to_int(arena, start_idx, len);
	cr_expect_eq(value, converted, "value = %d, converted from arena = %d\n", value, converted);
	unsigned int i = 0;
	unsigned char stored_byte;
	unsigned char value_byte;
	while (i < len)
	{
		stored_byte = arena[new_idx(start_idx, i, FALSE)];
		value_byte = ((unsigned char*)&value)[len - 1 - i];
		cr_expect_eq(stored_byte, value_byte, "stored_byte[%d]: %d, expected: %d\n", i, stored_byte, value_byte);
		++i;
	}
}



Test(store_in_arena, len_2_neg)
{
	unsigned int	len = 2;
	int				value = -42;
	unsigned int	start_idx = 0;

	unsigned char	arena[MEM_SIZE];
	ft_bzero(&arena, MEM_SIZE);
	store_in_arena(arena, start_idx, len, value);
	// int converted = convert_to_int(arena, start_idx, len);
	// cr_expect_eq(value, converted, "value = %d, converted from arena = %d\n", value, converted);
	unsigned int i = 0;
	unsigned char stored_byte;
	unsigned char value_byte;
	while (i < len)
	{
		stored_byte = arena[new_idx(start_idx, i, FALSE)];
		value_byte = ((unsigned char*)&value)[len - 1 - i];
		cr_expect_eq(stored_byte, value_byte, "stored_byte[%d]: %d, expected: %d\n", i, stored_byte, value_byte);
		++i;
	}
}

Test(store_in_arena, len_2_pos)
{
	unsigned int	len = 2;
	int				value = 42;
	unsigned int	start_idx = MEM_SIZE - 1;

	unsigned char	arena[MEM_SIZE];
	ft_bzero(&arena, MEM_SIZE);
	store_in_arena(arena, start_idx, len, value);
	int converted = convert_to_int(arena, start_idx, len);
	cr_expect_eq(value, converted, "value = %d, converted from arena = %d\n", value, converted);
	unsigned int i = 0;
	unsigned char stored_byte;
	unsigned char value_byte;
	while (i < len)
	{
		stored_byte = arena[new_idx(start_idx, i, FALSE)];
		value_byte = ((unsigned char*)&value)[len - 1 - i];
		cr_expect_eq(stored_byte, value_byte, "stored_byte[%d]: %d, expected: %d\n", i, stored_byte, value_byte);
		++i;
	}
}

Test(store_in_arena, len_2_one)
{
	unsigned int	len = 2;
	int				value = 1;
	unsigned int	start_idx = MEM_SIZE - 1;

	unsigned char	arena[MEM_SIZE];
	ft_bzero(&arena, MEM_SIZE);
	store_in_arena(arena, start_idx, len, value);
	int converted = convert_to_int(arena, start_idx, len);
	cr_expect_eq(value, converted, "value = %d, converted from arena = %d\n", value, converted);
	unsigned int i = 0;
	unsigned char stored_byte;
	unsigned char value_byte;
	while (i < len)
	{
		stored_byte = arena[new_idx(start_idx, i, FALSE)];
		value_byte = ((unsigned char*)&value)[len - 1 - i];
		cr_expect_eq(stored_byte, value_byte, "stored_byte[%d]: %d, expected: %d\n", i, stored_byte, value_byte);
		++i;
	}
}

Test(store_in_arena, len_2_zero)
{
	unsigned int	len = 2;
	int				value = 0;
	unsigned int	start_idx = MEM_SIZE - 1;

	unsigned char	arena[MEM_SIZE];
	ft_bzero(&arena, MEM_SIZE);
	store_in_arena(arena, start_idx, len, value);
	int converted = convert_to_int(arena, start_idx, len);
	cr_expect_eq(value, converted, "value = %d, converted from arena = %d\n", value, converted);
	unsigned int i = 0;
	unsigned char stored_byte;
	unsigned char value_byte;
	while (i < len)
	{
		stored_byte = arena[new_idx(start_idx, i, FALSE)];
		value_byte = ((unsigned char*)&value)[len - 1 - i];
		cr_expect_eq(stored_byte, value_byte, "stored_byte[%d]: %d, expected: %d\n", i, stored_byte, value_byte);
		++i;
	}
}



Test(store_in_arena, len_1_neg)
{
	unsigned int	len = 1;
	int				value = -5;
	unsigned int	start_idx = MEM_SIZE - 1;

	unsigned char	arena[MEM_SIZE];
	ft_bzero(&arena, MEM_SIZE);
	store_in_arena(arena, start_idx, len, value);
	// int converted = convert_to_int(arena, start_idx, len);
	// cr_expect_eq(value, converted, "value = %d, converted from arena = %d\n", value, converted);
	unsigned int i = 0;
	unsigned char stored_byte;
	unsigned char value_byte;
	while (i < len)
	{
		stored_byte = arena[new_idx(start_idx, i, FALSE)];
		value_byte = ((unsigned char*)&value)[len - 1 - i];
		cr_expect_eq(stored_byte, value_byte, "stored_byte[%d]: %d, expected: %d\n", i, stored_byte, value_byte);
		++i;
	}
}

Test(store_in_arena, len_1_pos)
{
	unsigned int	len = 1;
	int				value = 127;
	unsigned int	start_idx = MEM_SIZE - 1;

	unsigned char	arena[MEM_SIZE];
	ft_bzero(&arena, MEM_SIZE);
	store_in_arena(arena, start_idx, len, value);
	int converted = convert_to_int(arena, start_idx, len);
	cr_expect_eq(value, converted, "value = %d, converted from arena = %d\n", value, converted);
	unsigned int i = 0;
	unsigned char stored_byte;
	unsigned char value_byte;
	while (i < len)
	{
		stored_byte = arena[new_idx(start_idx, i, FALSE)];
		value_byte = ((unsigned char*)&value)[len - 1 - i];
		cr_expect_eq(stored_byte, value_byte, "stored_byte[%d]: %d, expected: %d\n", i, stored_byte, value_byte);
		++i;
	}
}

Test(store_in_arena, len_1_one)
{
	unsigned int	len = 1;
	int				value = 1;
	unsigned int	start_idx = MEM_SIZE - 1;

	unsigned char	arena[MEM_SIZE];
	ft_bzero(&arena, MEM_SIZE);
	store_in_arena(arena, start_idx, len, value);
	int converted = convert_to_int(arena, start_idx, len);
	cr_expect_eq(value, converted, "value = %d, converted from arena = %d\n", value, converted);
	unsigned int i = 0;
	unsigned char stored_byte;
	unsigned char value_byte;
	while (i < len)
	{
		stored_byte = arena[new_idx(start_idx, i, FALSE)];
		value_byte = ((unsigned char*)&value)[len - 1 - i];
		cr_expect_eq(stored_byte, value_byte, "stored_byte[%d]: %d, expected: %d\n", i, stored_byte, value_byte);
		++i;
	}
}

Test(store_in_arena, len_1_zero)
{
	unsigned int	len = 1;
	int				value = 0;
	unsigned int	start_idx = MEM_SIZE - 1;

	unsigned char	arena[MEM_SIZE];
	ft_bzero(&arena, MEM_SIZE);
	store_in_arena(arena, start_idx, len, value);
	int converted = convert_to_int(arena, start_idx, len);
	cr_expect_eq(value, converted, "value = %d, converted from arena = %d\n", value, converted);
	unsigned int i = 0;
	unsigned char stored_byte;
	unsigned char value_byte;
	while (i < len)
	{
		stored_byte = arena[new_idx(start_idx, i, FALSE)];
		value_byte = ((unsigned char*)&value)[len - 1 - i];
		cr_expect_eq(stored_byte, value_byte, "stored_byte[%d]: %d, expected: %d\n", i, stored_byte, value_byte);
		++i;
	}
}

////////////////////////////////////////////////////////////////////////////////
//	ARG_TYPE	ARG_TYPE	ARG_TYPE	ARG_TYPE	ARG_TYPE	ARG_TYPE	  //
////////////////////////////////////////////////////////////////////////////////

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
