/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_translate_to_bytecode.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 21:48:03 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/16 20:11:13 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "corewar.h"
#include "libft.h"
#include "asm.h"

#define TOKEN							((t_token*)temp->content)
#define NEXT_LIST						temp = temp->next;

// Test(test_translate_to_bytecode, mini_zork_test)
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


// /*----------------------------------------------------------------------------*/
// /*------------------------------- Test register to write -----------------------*/
// 	(void)type;
// 	while (i < 5)
// 	{
// 		NEXT_LIST
// 		i++;
// 	}	
// 	// ft_printf("literal %s\n", TOKEN->literal_str);
// 	file = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);
// 	// ft_printf("size %d\nstring %s\n", token_tab[REGISTER].size, TOKEN->literal_str + 1);
// 	write_str_to_buf(as, TOKEN->literal_str + 1, (unsigned char)token_tab[REGISTER].size);
// 	i = write(file, as->buffer, as->index);
// 	// ft_printf("fd = %d - sz = %d\n", file, i);

// /*----------------------------------------------------------------------------*/
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
// 	// ft_printf("fd = %d - sz = %d\n", file, i);
// }

Test(test_translate_to_bytecode, zork_test)
{
	t_project 	*as;
	// int			file;
	t_list		*temp;
	int			i;
	char		type;
	t_elem		*hash;

	i = 0;
	as = (t_project*)ft_memalloc(sizeof(t_project));
	// as->flags |= DEBUG_O;
	as->fd = open("./valid_asm/zork.s", O_RDONLY);
	if (as->fd == -1)
		ft_printf("error fd\n");
	if (!analyze_lexicon(as))
		ft_printf("error lex\n");
	if (!analyze_syntax(as))
		ft_printf("error syn\n");
	if (!analyze_instructions(as))
		ft_printf("error ins\n");
	if (!analyze_parameters(as))
		ft_printf("error ins\n");
	as->index = 0;
	as->buffer = (char*)ft_memalloc(sizeof(CHAMP_MAX_SIZE + 1));
	temp = as->token_list;

// /*----------------------------------------------------------------------------*/
// /*------------------------------- Test direct_label to write -----------------------*/
	// (void)type;
	// while (i < 4)
	// {
	// 	NEXT_LIST
	// 	i++;
	// }
	// as->opcode_temp = TOKEN->opcode;
	// NEXT_LIST
	// NEXT_LIST

	// if (as->labels == NULL)
	// 	ft_printf("hash table NULL\n");
	// hash = ((t_elem*)(as->labels[0].elem));
	// // hash = ft_hash_table_get(as->labels, label_to_key(TOKEN->literal_str, TOKEN->token_type));
	// if (hash == NULL)
	// 	ft_printf("return hash.get NULL\n");
	// ft_printf("literal [%s] - type [%d]\n", TOKEN->literal_str, TOKEN->token_type);
	// ft_printf("string [%s]\n", label_to_key(TOKEN->literal_str, TOKEN->token_type));
	// ft_printf("pc [%zu]\n", (size_t)hash->content);
// 	file = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);;
// 	// ft_printf("size %d\nstring %s\n", token_tab[REGISTER].size, TOKEN->literal_str + 1);
// 	write_str_to_buf(as, TOKEN->literal_str + 1, (unsigned char)token_tab[REGISTER].size);
// 	i = write(file, as->buffer, as->index);
// 	// ft_printf("fd = %d - sz = %d\n", file, i);


// /*----------------------------------------------------------------------------*/
// /*------------------------------- Test indirect to write -----------------------*/
	(void)type;
	(void)hash;
	while (i < 8)
	{
		NEXT_LIST
		i++;
	}
	as->opcode_temp = TOKEN->opcode;
	ft_printf("opcode [%d]\n", TOKEN->opcode);
	NEXT_LIST
	ft_printf("literal [%s] - type [%d]\n", TOKEN->literal_str, TOKEN->token_type);


	// ft_printf("string [%s]\n", label_to_key(TOKEN->literal_str, TOKEN->token_type));
	// ft_printf("pc [%zu]\n", (size_t)hash->content);
// 	file = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);;
// 	// ft_printf("size %d\nstring %s\n", token_tab[REGISTER].size, TOKEN->literal_str + 1);
// 	write_str_to_buf(as, TOKEN->literal_str + 1, (unsigned char)token_tab[REGISTER].size);
// 	i = write(file, as->buffer, as->index);
// 	// ft_printf("fd = %d - sz = %d\n", file, i);
}