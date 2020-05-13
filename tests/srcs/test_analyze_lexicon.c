/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_analyze_lexicon.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 10:18:45 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/13 20:56:40 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "corewar.h"
#include "libft.h"
#include "asm.h"

// Test(test_lexical_analysis, process_line_test)
// {
// 	t_project	*as;
// 	char 		*line;

// 	as = (t_project*)ft_memalloc(sizeof(t_project));
	
// 	line = ft_strdup("#hsdjhfjdhtest");
// 	process_line(as, &line);
// 	cr_assert_str_eq(line, "");

// 	line = ft_strdup(";hsdjhfjdhtest");
// 	process_line(as, &line);
// 	cr_assert_str_eq(line, "");

// 	line = ft_strdup("   \t  \v  \f    test   ");
// 	process_line(as, &line);
// 	cr_assert_str_eq(line, "test   ");


// }

// 

Test(test_lexical_analysis, command_token_test)
{
	t_project	*as;
	char 		*line;
	t_bool		ret;
	t_list		*temp;

	as = (t_project*)ft_memalloc(sizeof(t_project));

	line = ft_strdup(".name   \t");
	command_token(as, &line);
	temp = as->token_list;
	cr_assert(((t_token*)temp->content)->token_type == COMMAND_NAME);

	line = ft_strdup(".comment   \t");
	command_token(as, &line);
	temp = as->token_list->next;
	cr_assert(((t_token*)temp->content)->token_type == COMMAND_COMMENT);

	line = ft_strdup(".extwebndsdfa   \t");
	ret = command_token(as, &line);
	temp = as->token_list->next;
	cr_assert(ret == FAIL);
}

Test(test_lexical_analysis, direct_token_test)
{
	t_project	*as;
	char 		*line;
	t_bool		ret;
	t_list		*temp;

	as = (t_project*)ft_memalloc(sizeof(t_project));
	as->row = 4;
	as->column = 10;

	line = ft_strdup("%hfh");
	as->temp = line;
	ret = direct_token(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 11);
	// ft_printf(LEXICAL_ERR, as->row, as->column);
	
	as->column = 10;
	line = ft_strdup("%+54");
	as->temp = line;
	ret = direct_token(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 11);
	// ft_printf(LEXICAL_ERR, as->row, as->column);

	as->column = 10;
	line = ft_strdup("%:43]jg\t");
	as->temp = line;
	ret = direct_token(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 14);

	as->column = 10;
	line = ft_strdup("%-43jg");
	as->temp = line;
	ret = direct_token(as, &line);
	temp = as->token_list;
	cr_assert(((t_token*)temp->content)->token_type == DIRECT);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 14);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "%-43");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup("%-0jg");
	as->temp = line;
	ret = direct_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == DIRECT);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 13);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "%-0");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup("%0007234jg");
	as->temp = line;
	ret = direct_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == DIRECT);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 18);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "%0007234");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup("%:43jg\t");
	as->temp = line;
	ret = direct_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == DIRECT_LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 16);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "%:43jg");
	cr_assert(((t_token*)temp->content)->column == 10);
	
}

Test(test_lexical_analysis, direct_label_token_test)
{
	t_project	*as;
	char 		*line;
	t_bool		ret;
	t_list		*temp;

	as = (t_project*)ft_memalloc(sizeof(t_project));
	as->row = 4;

	as->column = 10;
	line = ft_strdup(":h.fh");
	as->temp = line;
	ret = direct_label_token(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 12);
	// ft_printf(LEXICAL_ERR, as->row, as->column);
	
	as->column = 10;
	line = ft_strdup(":5F4");
	as->temp = line;
	ret = direct_label_token(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 12);
	// ft_printf(LEXICAL_ERR, as->row, as->column);

	as->column = 10;
	line = ft_strdup(":43jg\t");
	as->temp = line;
	ret = direct_label_token(as, &line);
	temp = as->token_list;
	cr_assert(((t_token*)temp->content)->token_type == DIRECT_LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 15);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":43jg");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup(":8sdf%");
	as->temp = line;
	ret = direct_label_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == DIRECT_LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 15);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":8sdf");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup(":8sdf,");
	as->temp = line;
	ret = direct_label_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == DIRECT_LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 15);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":8sdf");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup(":8sdf#");
	as->temp = line;
	ret = direct_label_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == DIRECT_LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 15);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":8sdf");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup(":8sdf;");
	as->temp = line;
	ret = direct_label_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == DIRECT_LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 15);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":8sdf");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup(":8sdf\"sdfsd\"");
	as->temp = line;
	ret = direct_label_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == DIRECT_LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 15);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":8sdf");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup(":8sdf ");
	as->temp = line;
	ret = direct_label_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == DIRECT_LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 15);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":8sdf");
	cr_assert(((t_token*)temp->content)->column == 10);
}


Test(test_lexical_analysis, indirect_label_token_test)
{
	t_project	*as;
	char 		*line;
	t_bool		ret;
	t_list		*temp;

	as = (t_project*)ft_memalloc(sizeof(t_project));
	as->row = 4;


	as->column = 10;
	line = ft_strdup(":.fh");
	as->temp = line;
	ret = indirect_label_token(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 11);
	// ft_printf(LEXICAL_ERR, as->row, as->column);

	as->column = 10;
	line = ft_strdup(":%.fh");
	as->temp = line;
	ret = indirect_label_token(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 11);
	// ft_printf(LEXICAL_ERR, as->row, as->column);

	as->column = 10;
	line = ft_strdup(":5F4");
	as->temp = line;
	ret = indirect_label_token(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 12);

	as->column = 10;
	line = ft_strdup(":43jg\t");
	as->temp = line;
	ret = indirect_label_token(as, &line);
	temp = as->token_list;
	cr_assert(((t_token*)temp->content)->token_type == INDIRECT_LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 15);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":43jg");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup(":8sdf%");
	as->temp = line;
	ret = indirect_label_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INDIRECT_LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 15);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":8sdf");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup(":8%fd");
	as->temp = line;
	ret = indirect_label_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INDIRECT_LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 12);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":8");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup(":8sdf,");
	as->temp = line;
	ret = indirect_label_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INDIRECT_LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 15);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":8sdf");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup(":8sdf#");
	as->temp = line;
	ret = indirect_label_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INDIRECT_LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 15);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":8sdf");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup(":8sdf;");
	as->temp = line;
	ret = indirect_label_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INDIRECT_LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 15);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":8sdf");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup(":8sdf ");
	as->temp = line;
	ret = indirect_label_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INDIRECT_LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 15);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":8sdf");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup(":8sdf\"sdsd\"");
	as->temp = line;
	ret = indirect_label_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INDIRECT_LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 15);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":8sdf");
	cr_assert(((t_token*)temp->content)->column == 10);
	
}

Test(test_lexical_analysis, skip_whitespaces_test)
{
	t_project	*as;
	char *test_string;

	as = (t_project*)ft_memalloc(sizeof(t_project));

	test_string = ft_strdup("   \t  \v  \f    test   ");
	skip_whitespaces(as, &test_string);
	cr_assert_str_eq(test_string, "test   ");

	test_string = ft_strdup(" ");
	skip_whitespaces(as, &test_string);
	cr_assert_str_eq(test_string, "");
}

Test(test_lexical_analysis, skip_comment_line_test)
{
	t_project	*as;
	char 		*line;

	as = (t_project*)ft_memalloc(sizeof(t_project));
	
	line = ft_strdup("#hsdjhfjdhtest");
	skip_comment_line(as, &line);
	cr_assert_str_eq(line, "");
}

Test(test_lexical_analysis, label_chars_redirect_test)
{
	t_project	*as;
	char 		*line;
	t_bool		ret;
	t_list		*temp;

	as = (t_project*)ft_memalloc(sizeof(t_project));
	as->row = 4;

	as->column = 0;
	line = ft_strdup("h.fh");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 1);
	// ft_printf(LEXICAL_ERR, as->row, (as->column + 1));
	
	as->column = 0;
	line = ft_strdup("f5F4");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 2);
	// ft_printf(LEXICAL_ERR, as->row, (as->column + 1));

	as->column = 0;
	line = ft_strdup("f!5F4");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 1);
	// ft_printf(LEXICAL_ERR, as->row, (as->column + 1));

	as->column = 0;
	line = ft_strdup("r0 f!5F4");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 1);
	// ft_printf(LEXICAL_ERR, as->row, (as->column + 1));
	
	as->column = 0;
	line = ft_strdup("r00 f!5F4");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 2);
	// ft_printf(LEXICAL_ERR, as->row, (as->column + 1));

	as->column = 0;
	line = ft_strdup("43jg\t");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = as->token_list;
	cr_assert(((t_token*)temp->content)->token_type == INSTRUCTION);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 4);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "43jg");
	cr_assert(((t_token*)temp->content)->column == 0);

	as->column = 10;
	line = ft_strdup("8sdf:%");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 15);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "8sdf:");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup("8:sdf:%");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 12);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "8:");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup("r1:sdf:%");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 13);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "r1:");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup("r14:sdf:%");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 14);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "r14:");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup("r14sdf:%");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 17);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "r14sdf:");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup("r144sdf:%");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 18);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "r144sdf:");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup("8sdf%");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INSTRUCTION);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 14);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "8sdf");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup("8sdf,");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INSTRUCTION);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 14);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "8sdf");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup("8sdf#");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INSTRUCTION);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 14);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "8sdf");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup("8sdf;");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INSTRUCTION);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 14);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "8sdf");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup("8sdf\"sdfsd\"");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INSTRUCTION);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 14);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "8sdf");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup("8sdf ");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INSTRUCTION);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 14);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "8sdf");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup("8sdf");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INSTRUCTION);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 14);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "8sdf");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 0;
	line = ft_strdup("r144sdf%");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INSTRUCTION);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 7);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "r144sdf");
	cr_assert(((t_token*)temp->content)->column == 0);

	as->column = 0;
	line = ft_strdup("r14 sdf%");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == REGISTER);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 3);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "r14");
	cr_assert(((t_token*)temp->content)->column == 0);

	as->column = 0;
	line = ft_strdup("r1 sdf%");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == REGISTER);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 2);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "r1");
	cr_assert(((t_token*)temp->content)->column == 0);

	as->column = 0;
	line = ft_strdup("r01 sdf%");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == REGISTER);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 3);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "r01");
	cr_assert(((t_token*)temp->content)->column == 0);

	as->column = 10;
	line = ft_strdup("000jdf\t");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INSTRUCTION);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 16);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "000jdf");
	cr_assert(((t_token*)temp->content)->column == 10);


	as->column = 10;
	line = ft_strdup("000jdf:\t");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 17);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "000jdf:");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup("000 jdf\t");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INDIRECT);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 13);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "000");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup("9039 jdf\t");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INDIRECT);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 14);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "9039");
	cr_assert(((t_token*)temp->content)->column == 10);
}

Test(test_lexical_analysis, register_token_test)
{
	t_project	*as;
	char 		*line;
	t_bool		ret;
	t_list		*temp;

	as = (t_project*)ft_memalloc(sizeof(t_project));
	as->row = 4;

	as->column = 0;
	line = ft_strdup("r0 ");
	as->temp = line;
	ret = register_token(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 1);
	// ft_printf(LEXICAL_ERR, as->row, (as->column + 1));
	
	as->column = 0;
	line = ft_strdup("r00;");
	as->temp = line;
	ret = register_token(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 2);
	// ft_printf(LEXICAL_ERR, as->row, (as->column + 1));

	as->column = 0;
	line = ft_strdup("r8\t");
	as->temp = line;
	ret = register_token(as, &line);
	temp = as->token_list;
	cr_assert(((t_token*)temp->content)->token_type == REGISTER);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 2);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "r8");
	cr_assert(((t_token*)temp->content)->column == 0);

	as->column = 10;
	line = ft_strdup("r93, ");
	as->temp = line;
	ret = register_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == REGISTER);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 13);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "r93");
	cr_assert(((t_token*)temp->content)->column == 10);
}

Test(test_lexical_analysis, indirect_token_test)
{
	t_project	*as;
	char 		*line;
	t_bool		ret;
	t_list		*temp;

	as = (t_project*)ft_memalloc(sizeof(t_project));
	as->row = 4;

	as->column = 0;
	line = ft_strdup("-+ ");
	as->temp = line;
	ret = indrect_token(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 0);
	// ft_printf(LEXICAL_ERR, as->row, (as->column + 1));
	
	as->column = 0;
	line = ft_strdup("- ;");
	as->temp = line;
	ret = indrect_token(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 0);
	// ft_printf(LEXICAL_ERR, as->row, (as->column + 1));

	as->column = 0;
	line = ft_strdup("-f ;");
	as->temp = line;
	ret = indrect_token(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 0);
	// ft_printf(LEXICAL_ERR, as->row, (as->column + 1));

	as->column = 0;
	line = ft_strdup("-0\t");
	as->temp = line;
	ret = indrect_token(as, &line);
	temp = as->token_list;
	cr_assert(((t_token*)temp->content)->token_type == INDIRECT);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 2);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "-0");
	cr_assert(((t_token*)temp->content)->column == 0);

	as->column = 10;
	line = ft_strdup("-8729+");
	as->temp = line;
	ret = indrect_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INDIRECT);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 15);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "-8729");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup("8729+");
	as->temp = line;
	ret = indrect_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INDIRECT);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 14);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "8729");
	cr_assert(((t_token*)temp->content)->column == 10);

	as->column = 10;
	line = ft_strdup("000jdf");
	as->temp = line;
	ret = indrect_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INDIRECT);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 13);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "000");
	cr_assert(((t_token*)temp->content)->column == 10);
}