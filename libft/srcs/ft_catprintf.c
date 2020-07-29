/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_catprintf.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgross <mgross@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 08:43:41 by mgross        #+#    #+#                 */
/*   Updated: 2020/07/29 10:19:28 by mgross        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_conversions(t_conversion_table *conversions)
{
	(*conversions)['D' - CONV_CHAR_START] = launch_int10;
	(*conversions)['d' - CONV_CHAR_START] = launch_int10;
	(*conversions)['i' - CONV_CHAR_START] = launch_int10;
	(*conversions)['I' - CONV_CHAR_START] = launch_int10;
	(*conversions)['u' - CONV_CHAR_START] = launch_int10_unsgnd;
	(*conversions)['U' - CONV_CHAR_START] = launch_int10_unsgnd;
	(*conversions)['b' - CONV_CHAR_START] = launch_int2;
	(*conversions)['B' - CONV_CHAR_START] = launch_int2;
	(*conversions)['o' - CONV_CHAR_START] = launch_int8;
	(*conversions)['O' - CONV_CHAR_START] = launch_int8;
	(*conversions)['x' - CONV_CHAR_START] = launch_int16;
	(*conversions)['X' - CONV_CHAR_START] = launch_int16;
	(*conversions)['p' - CONV_CHAR_START] = launch_int16;
	(*conversions)['P' - CONV_CHAR_START] = launch_int16;
	(*conversions)['f' - CONV_CHAR_START] = launch_double;
	(*conversions)['F' - CONV_CHAR_START] = launch_double;
	(*conversions)['c' - CONV_CHAR_START] = launch_c;
	(*conversions)['C' - CONV_CHAR_START] = launch_c;
	(*conversions)['s' - CONV_CHAR_START] = launch_s;
	(*conversions)['S' - CONV_CHAR_START] = launch_s;
	(*conversions)['n' - CONV_CHAR_START] = launch_n;
}

/*
** -------------------------------------------------------------------------- **
** when conversion character is found this function is called
** initialises the conversion-launcher function table
** loops through all following conversions and prints the stuff after each
** conversion
**
** params
**	t_conversion_table	conversions	the table of functionpointers
**	char				*pos		the pointer to the character after the
**									conversion characater '%'
**	va_list				ap			list item for the next conversion argument
**	t_buffer			*buf		addres of the struct holding all info for
**									the buffer
** return
**	VOID
*/

static void	start_conv(const t_conversion_table conversions, char *pos,
	va_list ap, t_buffer *buf)
{
	t_flags				flags;
	char				*next_conv;

	while (*pos != 0)
	{
		ft_bzero(&flags, sizeof(flags));
		pos = save_flags(ap, pos, &flags);
		flags.conv = *pos;
		if (*pos >= CONV_CHAR_START && *pos < CONV_CHAR_END &&
			conversions[(int)*pos - CONV_CHAR_START] != NULL)
			conversions[(int)*pos - CONV_CHAR_START](ap, buf, &flags);
		else if (*pos)
			handle_char(*pos, buf, &flags);
		next_conv = ft_strchr(pos + (*pos == '%'), '%');
		if (next_conv)
		{
			buff_push(buf, pos + 1, (next_conv - (pos + 1)));
			pos = ++next_conv;
		}
		else
		{
			buff_push(buf, pos + 1, ft_strlen(pos) - 1);
			return ;
		}
	}
}

/*
** -------------------------------------------------------------------------- **
** start of the printf function
** creates the buffer-struct and the function-pointer array for the conversion-
** launchers
**
** params
**	int			fd		file description for output
**	const char	*format	the string to be printed
**	va_list		ap		list item for the next conversion argument
** return
**	int					number of printed bytes
*/

static char	*start_printf(const int fd, const char *format, va_list ap)
{
	t_buffer					buf;
	char						*pos;
	static t_conversion_table	conversions;

	if (conversions[0] == NULL)
		set_conversions(&conversions);
	pos = ft_strchr(format, '%');
	if (pos == NULL)
		return (ft_strdup(format));
	ft_bzero(&buf, sizeof(buf));
	buf.fd = fd;
	buff_push(&buf, (char*)format, (pos - format));
	++pos;
	start_conv(conversions, pos, ap, &buf);
	buf.idx ? buff_print_dump(&buf) : 0;
	va_end(ap);
	return (buf.sprint_buf);
}

char    *ft_catprintf(char *old_str, const char *format, ...)
{
    char    *new_str;
    char     *temp;
    va_list ap;

    va_start(ap, format);
    new_str = start_printf(-2, format, ap);
    temp = new_str;
    new_str = ft_strjoin(old_str, new_str);
    free(temp);
    return (new_str);
}
