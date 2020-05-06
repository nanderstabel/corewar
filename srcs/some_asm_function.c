#include "libft.h"
#include "asm.h"

void some_asm_function(char *s)
{
	if (ft_isint(s))
		ft_printf("%s is an integer\n", s);
	else
		ft_printf("%s is not an integer\n", s);
}
