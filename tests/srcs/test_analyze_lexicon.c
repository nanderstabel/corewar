/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_analyze_lexicon.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 10:18:45 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/12 17:01:07 by zitzak        ########   odam.nl         */
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

Test(test_lexical_analysis, direct_token_test)
{
	t_project	*as;
	char 		*line;

	as = (t_project*)ft_memalloc(sizeof(t_project));

	line = ft_strdup("%:jkdf");
	direct_token(as, &line);
	

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



	
