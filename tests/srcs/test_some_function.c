#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "corewar.h"
#include "libft.h"

void	redirect_all_stdout(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

Test(some_function, valid_pos, .init=redirect_all_stdout)
{
	char	*input = "3878032";
	some_function(input);
	cr_assert_stdout_eq_str("3878032 is an integer\n", "");
}
