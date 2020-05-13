/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_analyze_lexicon.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 10:18:45 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/13 16:39:15 by zitzak        ########   odam.nl         */
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

Test(test_lexical_analysis, label_token_test)
{
	t_project	*as;
	char 		*line;
	t_bool		ret;
	// t_list		*temp;

	as = (t_project*)ft_memalloc(sizeof(t_project));
	as->row = 4;

	as->column = 0;
	line = ft_strdup("h.fh");
	as->temp = line;
	ret = label_token(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 1);
	ft_printf(LEXICAL_ERR, as->row, (as->column + 1));
	
	as->column = 0;
	line = ft_strdup(":5F4");
	as->temp = line;
	ret = label_token(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 2);
	ft_printf(LEXICAL_ERR, as->row, (as->column + 1));

	// as->column = 10;
	// line = ft_strdup(":43jg\t");
	// as->temp = line;
	// ret = label_token(as, &line);
	// temp = as->token_list;
	// cr_assert(((t_token*)temp->content)->token_type == DIRECT_LABEL);
	// cr_assert(ret == SUCCESS);
	// cr_assert(as->column == 15);
	// cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":43jg");
	// cr_assert(((t_token*)temp->content)->column == 10);

	// as->column = 10;
	// line = ft_strdup(":8sdf%");
	// as->temp = line;
	// ret = label_token(as, &line);
	// temp = temp->next;
	// cr_assert(((t_token*)temp->content)->token_type == DIRECT_LABEL);
	// cr_assert(ret == SUCCESS);
	// cr_assert(as->column == 15);
	// cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":8sdf");
	// cr_assert(((t_token*)temp->content)->column == 10);

	// as->column = 10;
	// line = ft_strdup(":8sdf,");
	// as->temp = line;
	// ret = label_token(as, &line);
	// temp = temp->next;
	// cr_assert(((t_token*)temp->content)->token_type == DIRECT_LABEL);
	// cr_assert(ret == SUCCESS);
	// cr_assert(as->column == 15);
	// cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":8sdf");
	// cr_assert(((t_token*)temp->content)->column == 10);

	// as->column = 10;
	// line = ft_strdup(":8sdf#");
	// as->temp = line;
	// ret = label_token(as, &line);
	// temp = temp->next;
	// cr_assert(((t_token*)temp->content)->token_type == DIRECT_LABEL);
	// cr_assert(ret == SUCCESS);
	// cr_assert(as->column == 15);
	// cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":8sdf");
	// cr_assert(((t_token*)temp->content)->column == 10);

	// as->column = 10;
	// line = ft_strdup(":8sdf;");
	// as->temp = line;
	// ret = label_token(as, &line);
	// temp = temp->next;
	// cr_assert(((t_token*)temp->content)->token_type == DIRECT_LABEL);
	// cr_assert(ret == SUCCESS);
	// cr_assert(as->column == 15);
	// cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":8sdf");
	// cr_assert(((t_token*)temp->content)->column == 10);

	// as->column = 10;
	// line = ft_strdup(":8sdf\"sdfsd\"");
	// as->temp = line;
	// ret = label_token(as, &line);
	// temp = temp->next;
	// cr_assert(((t_token*)temp->content)->token_type == DIRECT_LABEL);
	// cr_assert(ret == SUCCESS);
	// cr_assert(as->column == 15);
	// cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":8sdf");
	// cr_assert(((t_token*)temp->content)->column == 10);

	// as->column = 10;
	// line = ft_strdup(":8sdf ");
	// as->temp = line;
	// ret = label_token(as, &line);
	// temp = temp->next;
	// cr_assert(((t_token*)temp->content)->token_type == DIRECT_LABEL);
	// cr_assert(ret == SUCCESS);
	// cr_assert(as->column == 15);
	// cr_assert_str_eq(((t_token*)temp->content)->literal_str, ":8sdf");
	// cr_assert(((t_token*)temp->content)->column == 10);
}