/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_translate_to_bytecode.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 21:48:03 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/15 22:47:31 by zitzak        ########   odam.nl         */
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

Test(test_translate_to_bytecode, translate_register_test)
{
	t_project 	*as;
	int			file;
	t_list		*temp;
	int			i;

	i = 0;
	as = (t_project*)ft_memalloc(sizeof(t_project));
	as->fd = open("./valid_asm/mini_zork.s", O_RDONLY);
	if (as->fd == -1)
		ft_printf("error fd\n");
	if (!analyze_lexicon(as))
		ft_printf("error lex\n");
	if (!analyze_syntax(as))
		ft_printf("error syn\n");
	if (!analyze_instructions(as))
		ft_printf("error ins\n");
	if (!analyze_parameters(as))
		ft_printf("error ins\n");\
	as->index = 0;
	as->buffer = (char*)ft_memalloc(sizeof(CHAMP_MAX_SIZE + 1));
	temp = as->token_list;
	while (i < 5)
	{
		NEXT_LIST
		i++;
	}	
	// ft_printf("literal %s\n", TOKEN->literal_str);

	file = open("./objs/test.cor", O_CREAT | O_RDWR, 00700);
	// ft_printf("size %d\nstring %s\n", token_tab[REGISTER].size, TOKEN->literal_str + 1);
	write_str_to_buf(as, TOKEN->literal_str + 1, (unsigned char)token_tab[REGISTER].size);
	
	i = write(file, as->buffer, as->index);
	// ft_printf("fd = %d - sz = %d\n", file, i);





}