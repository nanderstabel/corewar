/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm_label_to_key.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 12:04:40 by nstabel       #+#    #+#                 */
/*   Updated: 2020/05/15 12:11:07 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** -------------------------------------------------------------------------- **
** this function takes a string and a token type. If the token type is LABEL,
** a copy of the string without ':' at the end is returned. If the token is
** an INDIRECT_LABEL a copy without ':' at the beginning is returned and if the
** token is a DIRECT_LABEL, a copy without "%:" is returned
**	str					holds the name of the label
**	token				holds the type of the token
** return
**	NULL				in case of a failure
**	ft_strsub()			a new semi-copy of str
*/

char			*label_to_key(char *str, char token)
{
	if (token == LABEL)
		return (ft_strndup(str, ft_nchar(str, LABEL_CHAR) - 1));
	if (token == INDIRECT_LABEL)
		return (ft_strsub(str, 1, ft_strlen(str) - 1));
	if (token == DIRECT_LABEL)
		return (ft_strsub(str, 2, ft_strlen(str) - 2));
	return (NULL);
}
