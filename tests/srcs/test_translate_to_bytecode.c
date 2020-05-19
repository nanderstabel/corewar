/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_translate_to_bytecode.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 21:48:03 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/19 22:19:22 by zitzak        ########   odam.nl         */
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
// 	if (as->fd == -1)zork
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


// /*----------------------------------------------------------------------------*/
// /*------------------------------- Test register to write -----------------------*/

// 	while (i < 5)
// 	{
// 		NEXT_LIST
// 		i++;
// 	}	
// 	file = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);
// 	// ft_printf("size %d\nstring %s\n", token_tab[REGISTER].size, TOKEN->literal_str);

// 	write_str_to_buf(as, TOKEN->literal_str + 1, token_tab[REGISTER].size);
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
// 	char		type;

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

// 	/*----------------------------------------------------------------------------*/
// /* ------------------------------- Test direct to write -----------------------*/
// 	while (i < 6)
// 	{
// 		NEXT_LIST
// 		i++;
// 	}
// 	as->opcode_temp = 6;
// 	// ft_printf("literal %s\n", TOKEN->literal_str);
// 	file = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);
// 	if (op_tab[as->opcode_temp - 1].label)
// 		type = 2;
// 	else
// 		type = 4;
// 	// ft_printf("size %d\nstring %s\n", token_tab[REGISTER].size, TOKEN->literal_str + 1);
// 	write_str_to_buf(as, TOKEN->literal_str + 1, type);
// 	i = write(file, as->buffer, as->index);
// 	system("xxd -b ./objs/test.cor");
// 	cr_assert_stdout_eq_str("00000000: 00000000 00000000 00000000 00000000                    ....\n");
// 	system("rm ./objs/test.cor");


// 	// ft_printf("fd = %d - sz = %d\n", file, i);
// }





// Test(test_translate_to_bytecode, direct_label_test1, .init=redirect_all_stdout_byte)
// {
// 	t_project 	*as;
// 	int			file;
// 	t_list		*temp;
// 	int			i;
// 	t_elem		*hash;
// 	char		*number;
// 	int			num_temp;

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

// /*----------------------------------------------------------------------------*/
// /*------------------------------- Test direct_label to write -----------------------*/
// 	while (i < 4)
// 	{
// 		NEXT_LIST
// 		i++;
// 	}
// 	as->opcode_temp = TOKEN->opcode;
// 	as->pc = TOKEN->address;
// 	NEXT_LIST
// 	NEXT_LIST
// 	if (as->labels == NULL)
// 		ft_printf("hash table NULL\n");
// 	hash = ((t_elem*)(as->labels[0].elem));
// 	hash = ft_hash_table_get(as->labels, label_to_key(TOKEN->literal_str, TOKEN->token_type));
// 	if (hash == NULL)
// 		ft_printf("return hash.get NULL\n");
// 	if (as->pc > (size_t)hash->content)
// 		num_temp = ((long long)hash->content - (long long)as->pc);
// 	else
// 			num_temp = (long long)as->pc + (long long)hash->content;
// 	// ft_printf("num_temp %d\n", num_temp);

// 	number = ft_itoa(num_temp);
// 	// ft_printf("literal [%s] - type [%d]\n current instruction pc [%zu] - PC in hash [%zu]\n", TOKEN->literal_str, TOKEN->token_type, as->pc, (size_t)hash->content);
// 	file = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);;
// 	write_str_to_buf(as, number, (unsigned char)token_tab[DIRECT_LABEL].size);
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
// 		ft_printf("error lex\n");zork
// 	if (!analyze_syntax(as))
// 		ft_printf("error syn\n");
// 	if (!analyze_instructions(as))
// 		ft_printf("error ins\n");
// 	if (!analyze_parameters(as))
// 		ft_printf("error ins\n");
// 	as->index = 0;
// 	as->buffer = (char*)ft_memalloc(sizeof(CHAMP_MAX_SIZE + 1));
// 	temp = as->token_list;

// /*----------------------------------------------------------------------------*/
// /*------------------------------- Test indirect to write -----------------------*/

// 	while (i < 8)
// 	{
// 		NEXT_LIST
// 		i++;
// 	}
// 	as->opcode_temp = TOKEN->opcode;
// 	// ft_printf("opcode [%d]\n", TOKEN->opcode);
// 	NEXT_LIST
// 	// ft_printf("literal [%s] - type [%d]\n", TOKEN->literal_str, TOKEN->token_type);

// 	file = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);;
// 	write_str_to_buf(as, TOKEN->literal_str, (unsigned char)token_tab[INDIRECT].size);
// 	i = write(file, as->buffer, as->index);
// 	system("xxd -b ./objs/test.cor");
// 	cr_assert_stdout_eq_str("00000000: 11111111 11111100                                      ..\n");
// 	system("rm ./objs/test.cor");
// 	// ft_printf("fd = %d - sz = %d\n", file, i);
// }

// Test(test_translate_to_bytecode, indirect_test1, .init=redirect_all_stdout_byte)
// {
// 	t_project 	*as;
// 	int			file;
// 	t_list		*temp;
// 	int			i;
// 	t_elem		*hash;
// 	char		*number;
// 	int			num_temp;


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
// 	// ft_printf("opcode [%d]\n", TOKEN->opcode);
// 	NEXT_LIST
// 	// ft_printf("literal [%s] - type [%d]\n", TOKEN->literal_str, TOKEN->token_type);
// 		hash = ((t_elem*)(as->labels[0].elem));
// 	hash = ft_hash_table_get(as->labels, label_to_key(TOKEN->literal_str, TOKEN->token_type));
// 	if (hash == NULL)
// 		ft_printf("return hash.get NULL\n");
// 	if (as->pc > (size_t)hash->content)
// 	{
// 		num_temp = ((long long)hash->content - (long long)as->pc);

// 	}
// 	else
// 	{
// 			num_temp = (long long)as->pc - (long long)hash->content;
// 	}
// 	// ft_printf("num_temp %d\n", num_temp);
// 	number = ft_itoa(num_temp);
// 	// number = ft_itoa((long long)hash->content);
// 	// ft_printf("literal [%s] - type [%d]\n current instruction pc [%zu] - PC in hash [%zu]\n", TOKEN->literal_str, TOKEN->token_type, as->pc, (size_t)hash->content);
// 	file = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);;
// 	write_str_to_buf(as, number, (unsigned char)token_tab[INDIRECT_LABEL].size);
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
// 	as->flags |= DEBUG_O;
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

// 	system("hexdump ./objs/test.cor");
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

// 	system("hexdump ./objs/test.cor");
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

// 	system("hexdump ./objs/test.cor");
// 	ft_printf("expected:\n         02 90 00 00 00 00 02\n");
// 	// cr_assert_stdout_eq_str("00000000: 11111111 11110000                                      ..\n");
// 	system("rm ./objs/test.cor");
// }

// Test(test_translate_to_bytecode, cookbook_batman_test)
// {
// 	t_project 	*as;
// 	int			file;
// 	int			i;

// 	i = 0;
// 	as = (t_project*)ft_memalloc(sizeof(t_project));
// 	// as->flags |= DEBUG_O;
// 	as->fd = open("./valid_asm/cookbook_batman.s", O_RDONLY);
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

// 	file = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);
// 	while ((size_t)i < as->index)
// 	{
// 		write(file, as->buffer, 1);
// 		as->buffer++;
// 		i++;
// 	}
	
// 	// write(file, as->buffer, as->index);
// 	// ft_printf("bytes writen = %d\nindex = %d\n", i, as->index);

// 	system("hexdump ./objs/test.cor");
// 	ft_printf("expected:\n         0b68 0100 0700 0101 0000 0000 0290 0000 0000 0209 ffed\n");
// 	// cr_assert_stdout_eq_str("00000000: 11111111 11110000                                      ..\n");
// 	system("rm ./objs/test.cor");
// }