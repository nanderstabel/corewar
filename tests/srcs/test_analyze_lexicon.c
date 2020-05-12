/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_analyze_lexicon.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 10:18:45 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/12 20:31:02 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "corewar.h"
#include "libft.h"
#include "asm.h"

Test(test_lexical_analysis, process_line_test)
{
	t_project	*as;
	char 		*line;

	as = (t_project*)ft_memalloc(sizeof(t_project));
	
	line = ft_strdup("#hsdjhfjdhtest");
	process_line(as, &line);
	cr_assert_str_eq(line, "");

	line = ft_strdup(";hsdjhfjdhtest");
	process_line(as, &line);
	cr_assert_str_eq(line, "");

	line = ft_strdup("   \t  \v  \f    test   ");
	process_line(as, &line);
	cr_assert_str_eq(line, "test   ");


}

// Test(test_lexical_analysis, direct_token_test)
// {
// 	t_project	*as;
// 	char 		*line;

// 	as = (t_project*)ft_memalloc(sizeof(t_project));

// 	line = ft_strdup("%:jkdf");
// 	direct_token(as, &line);
	

// }

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



	
