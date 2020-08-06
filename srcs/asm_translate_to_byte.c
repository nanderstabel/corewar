/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_translate_to_byte.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 19:27:58 by nstabel       #+#    #+#                 */
/*   Updated: 2020/08/06 18:08:29 by nstabel       ########   odam.nl         */
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

static t_bool	check_overflow(char **str)
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
		return (SUCCESS);
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

t_bool			translate_argument(t_project *as)
{
	int		offset;
	char	size;

	offset = 0;
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t\t%s\n", __func__) : 0;
	if (as->current_token->token_type == REGISTER ||
	as->current_token->token_type == DIRECT)
		offset = 1;
	if (as->current_token->token_type == DIRECT
	|| as->current_token->token_type == INDIRECT)
		check_overflow(&as->current_token->literal_str);
	if (as->current_token->token_type == DIRECT)
	{
		if (g_op_tab[as->opcode_temp - 1].label)
			size = 2;
		else
			size = 4;
	}
	else
		size = g_token_tab[as->current_token->token_type].size;
	write_str_to_buf(as, as->current_token->literal_str + offset, size);
	return (SUCCESS);
}

/*
** -------------------------------------------------------------------------- **
** translation_check checks whether the token type of the current token has a
** translate function stored in in the token table, if so, it calls that
** translate function and returnes whatever it return If there is no
** translate function stored, SUCCESS is returned.
** params
**	as->current_token	the current token
**	token_tab			token table
** return
**	.translate()		in case of available translate function
**	SUCCESS				if there is no need to translate
*/

t_bool			translation_check(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("\t%s\n", __func__) : 0;
	if (g_token_tab[as->current_token->token_type].translate)
		return (g_token_tab[as->current_token->token_type].translate(as));
	as->index = 0;
	return (SUCCESS);
}

/*
** -------------------------------------------------------------------------- **
** this is the main function for the translation to bytecode. It gives
** translation_check as an argument to loop_token_list and returns whatever
** loop_token_list returns.
** params
**	*as		project struct
** return
**	SUCCESS		in case the translation was successful
**	FAIL		in case the translation failed
*/

t_bool			translate_to_byte(t_project *as)
{
	as->count = (as->flags & DEBUG_O) ? ft_printf("%s\n", __func__) : 0;
	as->index = 0;
	as->buffer = (char*)ft_memalloc(CHAMP_MAX_SIZE);
	if (!as->buffer)
		return (FAIL);
	return (loop_token_list(as, translation_check));
}
