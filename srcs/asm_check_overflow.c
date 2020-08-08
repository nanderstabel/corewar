/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_check_overflow.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 14:59:10 by nstabel       #+#    #+#                 */
/*   Updated: 2020/08/07 15:10:44 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		create_max_value_string(char *str, char **max_value)
{
	int		index;

	if (*str == '%')
	{
		if (str[1] == '-')
			*max_value = ft_strdup("%-9223372036854775808");
		else
			*max_value = ft_strdup("%18446744073709551615");
		index = 1;
	}
	else
	{
		if (str[0] == '-')
			*max_value = ft_strdup("-9223372036854775808");
		else
			*max_value = ft_strdup("18446744073709551615");
		index = 0;
	}
	return (index);
}

static t_bool	return_free(char *max_value)
{
	free(max_value);
	return (SUCCESS);
}

t_bool			check_overflow(char **str)
{
	char	*max_value;
	int		index;

	index = create_max_value_string(*str, &max_value);
	if (ft_strlen(*str) > ft_strlen(max_value))
	{
		free(*str);
		*str = max_value;
		return (FAIL);
	}
	else if (ft_strlen(*str) < ft_strlen(max_value))
		return (return_free(max_value));
	while ((*str)[index] != '\0')
	{
		if ((*str)[index] > max_value[index])
		{
			free(*str);
			*str = max_value;
			return (SUCCESS);
		}
		index++;
	}
	free(max_value);
	return (SUCCESS);
}
