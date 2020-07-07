/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_analyze_lexicon.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 10:18:45 by zitzak        #+#    #+#                 */
/*   Updated: 2020/07/07 10:32:14 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "corewar.h"
#include "libft.h"
#include "asm.h"

void	redirect_all_stdout_lexical(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

Test(test_lexical_analysis, command_token_test)
{
	t_project	*as;
	char 		*line;
	t_bool		ret;
	t_list		*temp;

	as = (t_project*)ft_memalloc(sizeof(t_project));

	line = ft_strdup(".name   \t\n");
	command_token(as, &line);
	temp = as->token_list;
	cr_assert(((t_token*)temp->content)->token_type == COMMAND_NAME);

	line = ft_strdup(".comment   \n\t");
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

	line = ft_strdup("%hfh\n");
	as->temp = line;
	ret = direct_token(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 11);
	// ft_printf(LEXICAL_ERR, as->row, as->column);
	
	as->column = 10;
	line = ft_strdup("%+54\n");
	as->temp = line;
	ret = direct_token(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 11);
	// ft_printf(LEXICAL_ERR, as->row, as->column);

	as->column = 10;
	line = ft_strdup("%:43]jg\t\n");
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
	line = ft_strdup(":8sdf\n ");
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
	
	line = ft_strdup("#hsdjhfjdhtest\n");
	skip_comment_line(as, &line);
	cr_assert_str_eq(line, "\n");

	line = ft_strdup(";hsdjhfjdhtest\n");
	skip_comment_line(as, &line);
	cr_assert_str_eq(line, "\n");
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
	line = ft_strdup("43jg\n");
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
	line = ft_strdup("tirf:");
	as->temp = line;
	ret = label_chars_redirect(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == LABEL);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 15);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "tirf:");
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
	line = ft_strdup("8sdf\n");
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


	as->column = 10;
	line = ft_strdup("r43");
	as->temp = line;
	ret = register_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == REGISTER);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 13);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "r43");
	cr_assert(((t_token*)temp->content)->column == 10);
};

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

Test(test_lexical_analysis, string_token_test)
{
	t_project	*as;
	char 		*line;
	t_bool		ret;
	t_list		*temp;

	as = (t_project*)ft_memalloc(sizeof(t_project));
	as->row = 4;

	as->index = 0;
	as->column = 0;
	line = ft_strdup("\"sdkfjsdk\"F\n");
	as->temp = line;
	ret = string_token(as, &line);
	temp = as->token_list;
	cr_assert(((t_token*)temp->content)->token_type == STRING);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 10, "instead %zu", as->column);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "sdkfjsdk");
	cr_assert(((t_token*)temp->content)->column == 0);

	as->index = 0;
	as->column = 0;
	line = ft_strdup("\"898fjsdk\"\t");
	as->temp = line;
	ret = string_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == STRING);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 10, "instead %zu", as->column);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "898fjsdk");
	cr_assert(((t_token*)temp->content)->column == 0);

	as->index = 0;
	as->column = 0;
	line = ft_strdup("\"Dit is een n\n");
	as->temp = line;
	ret = string_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == STRING);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 13, "instead %zu", as->column);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "Dit is een n\n");
	cr_assert(((t_token*)temp->content)->column == 0);

	// as->index = 0;
	as->column = 0;
	line = ft_strdup("ieuwe test\"kdjf");
	as->temp = line;
	ret = string_token(as, &line);

	// temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == STRING);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 10, "instead %zu", as->column);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "Dit is een n\nieuwe test");
	cr_assert(((t_token*)temp->content)->column == 0);

	as->index = 0;
	as->column = 0;
	line = ft_strdup("\"Een wat lang\n");
	as->temp = line;
	ret = string_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == STRING);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 13, "instead %zu", as->column);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "Een wat lang\n");
	cr_assert(((t_token*)temp->content)->column == 0);

	// as->index = 0;
	as->column = 0;
	line = ft_strdup("ere test met t\n");
	as->temp = line;
	ret = string_token(as, &line);
	// temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == STRING);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 14, "instead %zu", as->column);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "Een wat lang\nere test met t\n");
	cr_assert(((t_token*)temp->content)->column == 0);

	as->column = 0;
	line = ft_strdup("wee keer een newline\" %f");
	as->temp = line;
	ret = string_token(as, &line);
	// temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == STRING);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 20, "instead %zu", as->column);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "Een wat lang\nere test met t\nwee keer een newline");
	cr_assert(((t_token*)temp->content)->column == 0);

}

Test(test_lexical_analysis, separator_token_test)
{
	t_project	*as;
	char 		*line;
	t_bool		ret;
	t_list		*temp;

	as = (t_project*)ft_memalloc(sizeof(t_project));
	as->row = 4;

	as->index = 0;
	as->column = 0;
	line = ft_strdup(",\"sdkfjsdk\"F");
	as->temp = line;
	ret = separator_token(as, &line);
	temp = as->token_list;
	cr_assert(((t_token*)temp->content)->token_type == SEPARATOR);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 1, "instead %zu", as->column);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, ",");
	cr_assert(((t_token*)temp->content)->column == 0);

	as->column = 12;
	line = ft_strdup(",asd\"898fjsdk\"\t");
	as->temp = line;
	ret = separator_token(as, &line);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == SEPARATOR);
	cr_assert(ret == SUCCESS);
	cr_assert(as->column == 13, "instead %zu", as->column);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, ",");
	cr_assert(((t_token*)temp->content)->column == 12);
}

Test(test_lexical_analysis, process_line_test)
{
	t_project	*as;
	char 		*line;
	t_bool		ret;
	t_list		*temp;

	as = (t_project*)ft_memalloc(sizeof(t_project));
	as->row = 4;


	as->column = 0;
	line = ft_strdup("Fls:\tbla");
	// as->temp = line;
	ret = process_line(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 0);
	// ft_printf(LEXICAL_ERR, as->row, (as->column + 1));

	as->column = 0;
	line = ft_strdup("+ls:\tbla");
	// as->temp = line;
	ret = process_line(as, &line);
	cr_assert(ret == FAIL);
	cr_assert(as->column == 0);
	// ft_printf(LEXICAL_ERR, as->row, (as->column + 1));

	// as->flags |= DEBUG_O;
	as->index = 0;
	as->column = 0;
	line = ft_strdup("entree: live\t%9");
	// as->temp = line;
	ret = process_line(as, &line);
	cr_assert(ret == SUCCESS);
	temp = as->token_list;
	cr_assert(((t_token*)temp->content)->token_type == LABEL);
	cr_assert(as->column == 15, "instead %zu", as->column);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "entree:");
	cr_assert(((t_token*)temp->content)->column == 0);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INSTRUCTION);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "live");
	cr_assert(((t_token*)temp->content)->column == 8);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == DIRECT);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "%9");
	cr_assert(((t_token*)temp->content)->column == 13);

	as->index = 0;
	as->column = 0;
	as->token_list = NULL;
	line = ft_strdup("entree:, liveF\t%9");
	// as->temp = line;
	ret = process_line(as, &line);
	cr_assert(ret == FAIL);
	// ft_printf(LEXICAL_ERR, as->row, (as->column + 1)); //hoort 14
	temp = as->token_list;
	cr_assert(((t_token*)temp->content)->token_type == LABEL);
	cr_assert(as->column == 13, "instead %zu", as->column);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "entree:");
	cr_assert(((t_token*)temp->content)->column == 0);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == SEPARATOR);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, ",");
	cr_assert(((t_token*)temp->content)->column == 7);
	temp = temp->next;
	cr_assert(temp == NULL);
}

Test(test_lexical_analysis, analyze_lexicon_test)
{
	t_project	*as;
	t_bool		ret;
	t_list		*temp;
	// char 		*line;

	as = (t_project*)ft_memalloc(sizeof(t_project));
	// as->flags |= DEBUG_O;
	// as->flags |= DEBUG_L;


	as->fd = open("./valid_asm/3_lines.s", O_RDONLY);
	as->index = 0;
	ret = analyze_lexicon(as);
	cr_assert(ret == SUCCESS);
	temp = as->token_list;
	cr_assert(((t_token*)temp->content)->token_type == LABEL);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "tirf:");
	cr_assert(((t_token*)temp->content)->column == 0);
	cr_assert(((t_token*)temp->content)->row == 0);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == ENDLINE);
	cr_assert(((t_token*)temp->content)->column == 5);
	cr_assert(((t_token*)temp->content)->row == 0);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INSTRUCTION);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "live");
	cr_assert(((t_token*)temp->content)->column == 2);
	cr_assert(((t_token*)temp->content)->row == 1);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == DIRECT);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "%42");
	cr_assert(((t_token*)temp->content)->column == 7);
	cr_assert(((t_token*)temp->content)->row == 1);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == ENDLINE);
	cr_assert(((t_token*)temp->content)->column == 10);
	cr_assert(((t_token*)temp->content)->row == 1);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INSTRUCTION);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "fork");
	cr_assert(((t_token*)temp->content)->column == 2);
	cr_assert(((t_token*)temp->content)->row == 2);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == DIRECT_LABEL);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "%:tirop");
	cr_assert(((t_token*)temp->content)->column == 7);
	cr_assert(((t_token*)temp->content)->row == 2);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == ENDLINE);
	cr_assert(((t_token*)temp->content)->column == 14);
	cr_assert(((t_token*)temp->content)->row == 2);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INSTRUCTION);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "ld");
	cr_assert(((t_token*)temp->content)->column == 2);
	cr_assert(((t_token*)temp->content)->row == 3);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INDIRECT);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "-8");
	cr_assert(((t_token*)temp->content)->column == 6);
	cr_assert(((t_token*)temp->content)->row == 3);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == SEPARATOR);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, ",");
	cr_assert(((t_token*)temp->content)->column == 9);
	cr_assert(((t_token*)temp->content)->row == 3);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == REGISTER);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "r43");
	cr_assert(((t_token*)temp->content)->column == 11);
	cr_assert(((t_token*)temp->content)->row == 3);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == ENDLINE);
	cr_assert(((t_token*)temp->content)->column == 14);
	cr_assert(((t_token*)temp->content)->row == 3);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == INSTRUCTION);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "live");
	cr_assert(((t_token*)temp->content)->column == 2);
	cr_assert(((t_token*)temp->content)->row == 4);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == DIRECT);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "%78");
	cr_assert(((t_token*)temp->content)->column == 7);
	cr_assert(((t_token*)temp->content)->row == 4);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == ENDLINE);
	cr_assert(((t_token*)temp->content)->column == 10);
	cr_assert(((t_token*)temp->content)->row == 4);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == END, "but is %d", ((t_token*)temp->content)->token_type);
	cr_assert(((t_token*)temp->content)->column == 0);
	cr_assert(((t_token*)temp->content)->row == 5);
	// temp = temp->next;
	// cr_assert(((t_token*)temp->content)->token_type == END);
	// cr_assert(((t_token*)temp->content)->column == 0);
	// cr_assert(((t_token*)temp->content)->row == 6);

}

Test(test_lexical_analysis, valid_asm_1line_test)
{
	t_project	*as;
	t_bool		ret;
	t_list		*temp;


	as = (t_project*)ft_memalloc(sizeof(t_project));
	// as->flags |= DEBUG_O;
	// as->flags |= DEBUG_L;

	as->fd = open("./invalid_asm/1_line.s", O_RDONLY);
	ret = analyze_lexicon(as);
	cr_assert(ret == SUCCESS);
	temp = as->token_list;
	cr_assert(((t_token*)temp->content)->token_type == LABEL);
	cr_assert_str_eq(((t_token*)temp->content)->literal_str, "tirf:");
	cr_assert(((t_token*)temp->content)->column == 0);
	cr_assert(((t_token*)temp->content)->row == 0);
	temp = temp->next;
	cr_assert(((t_token*)temp->content)->token_type == END);
	cr_assert(((t_token*)temp->content)->column == 5);
	cr_assert(((t_token*)temp->content)->row == 0);
}

Test(test_lexical_analysis, valid_asm_42_test)
{
	t_project	*as;
	t_bool		ret;


	as = (t_project*)ft_memalloc(sizeof(t_project));
	// as->flags |= DEBUG_O;
	// as->flags |= DEBUG_L;

	as->fd = open("./valid_asm/42.s", O_RDONLY);
	ret = analyze_lexicon(as);
	cr_assert(ret == SUCCESS);
}

Test(test_lexical_analysis, endlines__test)
{
	t_project	*as;
	t_bool		ret;


	as = (t_project*)ft_memalloc(sizeof(t_project));
	// as->flags |= DEBUG_O;
	// as->flags |= DEBUG_L;

	as->fd = open("./valid_asm/endlines.s", O_RDONLY);
	ret = analyze_lexicon(as);
	cr_assert(ret == SUCCESS);
}

Test(test_lexical_analysis, newline_strings_test)
{
	t_project	*as;
	t_bool		ret;


	as = (t_project*)ft_memalloc(sizeof(t_project));
	// as->flags |= DEBUG_O;
	// as->flags |= DEBUG_L;

	as->fd = open("./valid_asm/newline_string.s", O_RDONLY);
	ret = analyze_lexicon(as);
	cr_assert(ret == SUCCESS);
}

Test(test_lexical_analysis, lexical_error_small, .init=redirect_all_stdout_lexical)
{
	t_project	*as;


	as = (t_project*)ft_memalloc(sizeof(t_project));
	// as->flags |= DEBUG_O;
	// as->flags |= DEBUG_L;

	as->fd = open("./invalid_asm/lexical_error_small.s", O_RDONLY);
	analyze_lexicon(as);
	cr_assert_stderr_eq_str("Lexical error at [2:11]\n");

}

Test(test_lexical_analysis, lexical_error_01, .init=redirect_all_stdout_lexical)
{
	t_project	*as;


	as = (t_project*)ft_memalloc(sizeof(t_project));
	// as->flags |= DEBUG_O;
	// as->flags |= DEBUG_L;

	as->fd = open("./invalid_asm/lexical_error_01.s", O_RDONLY);
	analyze_lexicon(as);
	cr_assert_stderr_eq_str("Lexical error at [3:1]\n");

}

Test(test_lexical_analysis, lexical_error_02, .init=redirect_all_stdout_lexical)
{
	t_project	*as;


	as = (t_project*)ft_memalloc(sizeof(t_project));
	// as->flags |= DEBUG_O;
	// as->flags |= DEBUG_L;

	as->fd = open("./invalid_asm/lexical_error_02.s", O_RDONLY);
	analyze_lexicon(as);
	cr_assert_stderr_eq_str("Lexical error at [10:15]\n");
}

Test(test_lexical_analysis, lexical_error_03, .init=redirect_all_stdout_lexical)
{
	t_project	*as;


	as = (t_project*)ft_memalloc(sizeof(t_project));
	// as->flags |= DEBUG_O;
	// as->flags |= DEBUG_L;

	as->fd = open("./invalid_asm/lexical_error_03.s", O_RDONLY);
	analyze_lexicon(as);
	cr_assert_stderr_eq_str("Lexical error at [5:12]\n");
}

Test(test_lexical_analysis, lexical_error_04, .init=redirect_all_stdout_lexical)
{
	t_project	*as;


	as = (t_project*)ft_memalloc(sizeof(t_project));
	// as->flags |= DEBUG_O;
	// as->flags |= DEBUG_L;

	as->fd = open("./invalid_asm/lexical_error_04.s", O_RDONLY);
	analyze_lexicon(as);
	cr_assert_stderr_eq_str("Lexical error at [3:12]\n");
}

Test(test_lexical_analysis, lexical_error_05, .init=redirect_all_stdout_lexical)
{
	t_project	*as;


	as = (t_project*)ft_memalloc(sizeof(t_project));
	// as->flags |= DEBUG_O;
	// as->flags |= DEBUG_L;

	as->fd = open("./invalid_asm/lexical_error_05.s", O_RDONLY);
	analyze_lexicon(as);
	cr_assert_stderr_eq_str("Lexical error at [31:23]\n");
}

Test(test_lexical_analysis, lexical_error_06, .init=redirect_all_stdout_lexical)
{
	t_project	*as;


	as = (t_project*)ft_memalloc(sizeof(t_project));
	// as->flags |= DEBUG_O;
	// as->flags |= DEBUG_L;

	as->fd = open("./invalid_asm/lexical_error_06.s", O_RDONLY);
	analyze_lexicon(as);
	cr_assert_stderr_eq_str("Lexical error at [73:10]\n");
}

Test(test_lexical_analysis, lexical_error_07, .init=redirect_all_stdout_lexical)
{
	t_project	*as;


	as = (t_project*)ft_memalloc(sizeof(t_project));
	// as->flags |= DEBUG_O;
	// as->flags |= DEBUG_L;

	as->fd = open("./invalid_asm/lexical_error_07.s", O_RDONLY);
	analyze_lexicon(as);
	cr_assert_stderr_eq_str("Lexical error at [73:15]\n");
}

Test(test_lexical_analysis, valid_lexical_file)
{
	t_project	*as;
	t_bool		ret;


	as = (t_project*)ft_memalloc(sizeof(t_project));
	// as->flags |= DEBUG_O;
	// as->flags |= DEBUG_L;

	as->fd = open("./invalid_asm/syntax_error_24.s", O_RDONLY);
	ret = analyze_lexicon(as);
	cr_assert(ret == SUCCESS);
}