/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_buffer.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/03 14:18:51 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/08/08 08:21:02 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		catprintf_buf(t_buffer *buf)
{
	char	*temp;

	if (!buf->sprint_buf)
		buf->sprint_buf = ft_strdup(buf->str);
	else
	{
		temp = buf->sprint_buf;
		buf->sprint_buf = ft_strjoin(buf->sprint_buf, buf->str);
		free(temp);
	}
}

/*
** -------------------------------------------------------------------------- **
** copies n amount of characters from given string to fixed size buffer
** counts every character ever added to the buffer
** keeps track of the amount of characters currently in the buffer with idx
** prints buf when full
**
** params
**	t_buffer	*buf	address of the struct holding all info for the buffer
**	char		*str	string to be copied into the buffer
**	size_t		n		numbers of bytes to be printed
** return
**	VOID
*/

void			buff_push(t_buffer *buf, char *str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (buf->idx == BUFF_SIZE)
		{
			if (buf->fd == -2)
				catprintf_buf(buf);
			else
				ft_putnstr_fd(buf->str, BUFF_SIZE, buf->fd);
			buf->idx = 0;
		}
		buf->str[buf->idx] = str[i];
		++buf->idx;
		++buf->count;
		++i;
	}
}

/*
** -------------------------------------------------------------------------- **
** fills buf with n amount of the same given character
**
** params
**	t_buffer		*buf	address of the buffer struct
**	char			*c		character to fill buf with
**	unsigned int	n		amount of character to be added to buf
** return
**	VOID
*/

void			buff_filler(t_buffer *buf, char c, unsigned int n)
{
	char fill[n];

	ft_memset(&fill, c, n);
	buff_push(buf, fill, n);
}

/*
** -------------------------------------------------------------------------- **
** prints the remaining character in buf and resets index to 0
**
** params
**	t_buffer	*buf	address of the buffer struct
** return
**	VOID
*/

void			buff_print_dump(t_buffer *buf)
{
	char		*temp;

	if (buf->fd == -2)
		if (!buf->sprint_buf)
			buf->sprint_buf = ft_strdup(buf->str);
		else
		{
			temp = buf->sprint_buf;
			buf->sprint_buf = ft_strjoin(buf->sprint_buf, buf->str);
			free(temp);
		}
	else
		ft_putnstr_fd(buf->str, buf->idx, buf->fd);
	buf->idx = 0;
}
