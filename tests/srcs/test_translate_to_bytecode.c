/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_translate_to_bytecode.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 21:48:03 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/22 15:53:42 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "corewar.h"
#include "libft.h"
#include "asm.h"
#include <stdlib.h>

#define TOKEN							((t_token*)temp->content)
#define NEXT_LIST						temp = temp->next;

// static void redirect_all_stdout_byte(void)
// {
//         cr_redirect_stdout();
//         cr_redirect_stderr();
// }

// Test(test_translate_to_bytecode, register_test1, .init=redirect_all_stdout_byte)
// {
// 	t_project 	*as;
// 	int			file;
// 	t_list		*temp;
// 	int			i;

// 	i = 0;
// 	as = (t_project*)ft_memalloc(sizeof(t_project));
// 	as->fd = open("./valid_asm/mini_zork.s", O_RDONLY);
// 	if (as->fd == -1)
// 		ft_printf("error fd\n");
// 	if (!analyze_lexicon(as))
// 		ft_printf("error lex\n");
// 	if (!analyze_syntax(as))
// 		ft_printf("error syn\n");
// 	if (!analyze_instructions(as))
// 		ft_printf("error ins\n");
// 	if (!analyze_parameters(as))
// 		ft_printf("error ins\n");
// 	as->index = 0;
// 	as->buffer = (char*)ft_memalloc(sizeof(CHAMP_MAX_SIZE + 1));
// 	temp = as->token_list;
// 	while (i < 5)
// 	{
// 		NEXT_LIST
// 		i++;
// 	}
// 	as->current_token = TOKEN;
// 	file = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);
// 	translate_argument(as);
// 	i = write(file, as->buffer, as->index);
// 	system("xxd -b ./objs/test.cor");
// 	cr_assert_stdout_eq_str("00000000: 00000001                                               .\n");
// 	system("rm ./objs/test.cor");
// }


// Test(test_translate_to_bytecode, direct_test1, .init=redirect_all_stdout_byte)
// {
// 	t_project 	*as;
// 	int			file;
// 	t_list		*temp;
// 	int			i;

// 	i = 0;
// 	as = (t_project*)ft_memalloc(sizeof(t_project));
// 	as->fd = open("./valid_asm/mini_zork.s", O_RDONLY);
// 	if (as->fd == -1)
// 		ft_printf("error fd\n");
// 	if (!analyze_lexicon(as))
// 		ft_printf("error lex\n");
// 	if (!analyze_syntax(as))
// 		ft_printf("error syn\n");
// 	if (!analyze_instructions(as))
// 		ft_printf("error ins\n");
// 	if (!analyze_parameters(as))
// 		ft_printf("error ins\n");
// 	as->index = 0;
// 	as->buffer = (char*)ft_memalloc(sizeof(CHAMP_MAX_SIZE + 1));
// 	temp = as->token_list;
// 	while (i < 6)
// 	{
// 		NEXT_LIST
// 		i++;
// 	}
// 	as->opcode_temp = 6;
// 	as->current_token = TOKEN;
// 	file = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);
// 	translate_argument(as);
// 	i = write(file, as->buffer, as->index);
// 	system("xxd -b ./objs/test.cor");
// 	cr_assert_stdout_eq_str("00000000: 00000000 00000000 00000000 00000000                    ....\n");
// 	system("rm ./objs/test.cor");
// }


// Test(test_translate_to_bytecode, direct_label_test1, .init=redirect_all_stdout_byte)
// {
// 	t_project 	*as;
// 	int			file;
// 	t_list		*temp;
// 	int			i;

// 	i = 0;
// 	as = (t_project*)ft_memalloc(sizeof(t_project));
// 	as->fd = open("./valid_asm/zork.s", O_RDONLY);
// 	if (as->fd == -1)
// 		ft_printf("error fd\n");
// 	if (!analyze_lexicon(as))
// 		ft_printf("error lex\n");
// 	if (!analyze_syntax(as))
// 		ft_printf("error syn\n");
// 	if (!analyze_instructions(as))
// 		ft_printf("error ins\n");
// 	if (!analyze_parameters(as))
// 		ft_printf("error ins\n");
// 	as->index = 0;
// 	as->buffer = (char*)ft_memalloc(sizeof(CHAMP_MAX_SIZE + 1));
// 	temp = as->token_list;
// 	while (i < 4)
// 	{
// 		NEXT_LIST
// 		i++;
// 	}
// 	as->opcode_temp = TOKEN->opcode;
// 	as->pc = TOKEN->address;
// 	NEXT_LIST
// 	NEXT_LIST
// 	as->current_token = TOKEN;
// 	file = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);;
// 	translate_label(as);
// 	i = write(file, as->buffer, as->index);
// 	system("xxd -b ./objs/test.cor");
// 	cr_assert_stdout_eq_str("00000000: 00000000 00010000                                      ..\n");
// 	system("rm ./objs/test.cor");
// }


// Test(test_translate_to_bytecode, indirect_test1, .init=redirect_all_stdout_byte)
// {
// 	t_project 	*as;
// 	int			file;
// 	t_list		*temp;
// 	int			i;

// 	i = 0;
// 	as = (t_project*)ft_memalloc(sizeof(t_project));
// 	// as->flags |= DEBUG_O;
// 	as->fd = open("./valid_asm/zork.s", O_RDONLY);
// 	if (as->fd == -1)
// 		ft_printf("error fd\n");
// 	if (!analyze_lexicon(as))
// 		ft_printf("error lex\n");
// 	if (!analyze_syntax(as))
// 		ft_printf("error syn\n");
// 	if (!analyze_instructions(as))
// 		ft_printf("error ins\n");
// 	if (!analyze_parameters(as))
// 		ft_printf("error ins\n");
// 	as->index = 0;
// 	as->buffer = (char*)ft_memalloc(sizeof(CHAMP_MAX_SIZE + 1));
// 	temp = as->token_list;
// 	while (i < 8)
// 	{
// 		NEXT_LIST
// 		i++;
// 	}
// 	as->opcode_temp = TOKEN->opcode;
// 	NEXT_LIST
// 	as->current_token = TOKEN;
// 	file = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);
// 	translate_argument(as);
// 	i = write(file, as->buffer, as->index);
// 	system("xxd -b ./objs/test.cor");
// 	cr_assert_stdout_eq_str("00000000: 11111111 11111100                                      ..\n");
// 	system("rm ./objs/test.cor");
// }


// Test(test_translate_to_bytecode, indirect_label_test1, .init=redirect_all_stdout_byte)
// {
// 	t_project 	*as;
// 	int			file;
// 	t_list		*temp;
// 	int			i;

// 	i = 0;
// 	as = (t_project*)ft_memalloc(sizeof(t_project));
// 	// as->flags |= DEBUG_O;
// 	as->fd = open("./valid_asm/zork.s", O_RDONLY);
// 	if (as->fd == -1)
// 		ft_printf("error fd\n");
// 	if (!analyze_lexicon(as))
// 		ft_printf("error lex\n");
// 	if (!analyze_syntax(as))
// 		ft_printf("error syn\n");
// 	if (!analyze_instructions(as))
// 		ft_printf("error ins\n");
// 	if (!analyze_parameters(as))
// 		ft_printf("error ins\n");
// 	as->index = 0;
// 	as->buffer = (char*)ft_memalloc(sizeof(CHAMP_MAX_SIZE + 1));
// 	temp = as->token_list;
// 	while (i < 12)
// 	{
// 		NEXT_LIST
// 		i++;
// 	}
// 	as->opcode_temp = TOKEN->opcode;
// 	as->pc = TOKEN->address;
// 	NEXT_LIST
// 	as->current_token = TOKEN;
// 	file = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);;
// 	translate_label(as);
// 	i = write(file, as->buffer, as->index);
// 	system("xxd -b ./objs/test.cor");
// 	cr_assert_stdout_eq_str("00000000: 11111111 11110000                                      ..\n");
// 	system("rm ./objs/test.cor");
// }





// --------------------full line tests-----------------------





// Test(test_translate_to_bytecode, batman_line1_test)
// {
// 	t_project 	*as;
// 	int			file;
// 	// int			i;


// 	as = (t_project*)ft_memalloc(sizeof(t_project));
// 	// as->flags |= DEBUG_O;
// 	as->fd = open("./valid_asm/batman_line1.s", O_RDONLY);
// 	if (as->fd == -1)
// 		ft_printf("error fd\n");
// 	if (!analyze_lexicon(as))
// 		ft_printf("error lex\n");
// 	if (!analyze_syntax(as))
// 		ft_printf("error syn\n");
// 	if (!analyze_instructions(as))
// 		ft_printf("error ins\n");
// 	if (!analyze_parameters(as))
// 		ft_printf("error para\n");
// 	if (!translate_to_byte(as))
// 		ft_printf("error byte\n");

// 	file = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);;
// 	write(file, as->buffer, as->index);
// 	// ft_printf("bytes writen = %d\nindex = %d\n", i, as->index);
// 	system("xxd ./objs/test.cor");

// 	// system("hexdump ./objs/test.cor");
// 	ft_printf("expected:\n         0B 68 01 0007 0001\n");
// 	// cr_assert_stdout_eq_str("00000000: 11111111 11110000                                      ..\n");
// 	system("rm ./objs/test.cor");
// }

// Test(test_translate_to_bytecode, batman_line2_test)
// {
// 	t_project 	*as;
// 	int			file;
// 	// int			i;


// 	as = (t_project*)ft_memalloc(sizeof(t_project));
// 	// as->flags |= DEBUG_O;
// 	as->fd = open("./valid_asm/batman_line2.s", O_RDONLY);
// 	if (as->fd == -1)
// 		ft_printf("error fd\n");
// 	if (!analyze_lexicon(as))
// 		ft_printf("error lex\n");
// 	if (!analyze_syntax(as))
// 		ft_printf("error syn\n");
// 	if (!analyze_instructions(as))
// 		ft_printf("error ins\n");
// 	if (!analyze_parameters(as))
// 		ft_printf("error para\n");
// 	if (!translate_to_byte(as))
// 		ft_printf("error byte\n");

// 	file = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);;
// 	write(file, as->buffer, as->index);
// 	// ft_printf("bytes writen = %d\nindex = %d\n", i, as->index);
// 	system("xxd ./objs/test.cor");

// 	// system("hexdump ./objs/test.cor");
// 	ft_printf("expected:\n         01 0000 0000 \n");
// 	// cr_assert_stdout_eq_str("00000000: 11111111 11110000                                      ..\n");
// 	system("rm ./objs/test.cor");
// }

// Test(test_translate_to_bytecode, batman_line3_test)
// {
// 	t_project 	*as;
// 	int			file;
// 	// int			i;


// 	as = (t_project*)ft_memalloc(sizeof(t_project));
// 	// as->flags |= DEBUG_O;
// 	as->fd = open("./valid_asm/batman_line3.s", O_RDONLY);
// 	if (as->fd == -1)
// 		ft_printf("error fd\n");
// 	if (!analyze_lexicon(as))
// 		ft_printf("error lex\n");
// 	if (!analyze_syntax(as))
// 		ft_printf("error syn\n");
// 	if (!analyze_instructions(as))
// 		ft_printf("error ins\n");
// 	if (!analyze_parameters(as))
// 		ft_printf("error para\n");
// 	if (!translate_to_byte(as))
// 		ft_printf("error byte\n");

// 	file = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);;
// 	write(file, as->buffer, as->index);
// 	// ft_printf("bytes writen = %d\nindex = %d\n", i, as->index);

// 	system("xxd ./objs/test.cor");

// 	// system("hexdump ./objs/test.cor");
// 	ft_printf("expected:\n         02 90 00 00 00 00 02\n");
// 	// cr_assert_stdout_eq_str("00000000: 11111111 11110000                                      ..\n");
// 	system("rm ./objs/test.cor");
// }

Test(test_translate_to_bytecode, cookbook_batman_test)
{
	t_project 	*as;
	int			file;
	int			i;

	i = 0;
	as = (t_project*)ft_memalloc(sizeof(t_project));
	// as->flags |= DEBUG_O;
	as->fd = open("./valid_asm/cookbook_batman.s", O_RDONLY);
	if (as->fd == -1)
		ft_printf("error fd\n");
	if (!analyze_lexicon(as))
		ft_printf("error lex\n");
	if (!analyze_syntax(as))
		ft_printf("error syn\n");
	if (!analyze_instructions(as))
		ft_printf("error ins\n");
	if (!analyze_parameters(as))
		ft_printf("error para\n");
	if (!translate_to_byte(as))
		ft_printf("error byte\n");

	file = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);
	while ((size_t)i < as->index)
	{
		write(file, as->buffer, 1);
		as->buffer++;
		i++;
	}
	
	// write(file, as->buffer, as->index);
	// ft_printf("bytes writen = %d\nindex = %d\n", i, as->index);

	// system("hexdump ./objs/test.cor");
	system("xxd ./objs/test.cor");

	ft_printf("expected:\n         0b68 0100 0700 0101 0000 0000 0290 0000 0000 0209 ffed\n");
	// cr_assert_stdout_eq_str("00000000: 11111111 11110000                                      ..\n");
	system("rm ./objs/test.cor");
}