/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vis_cursor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 09:43:31 by lhageman      #+#    #+#                 */
/*   Updated: 2020/06/04 10:11:29 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

void	vis_calc_pos(t_graphics *graphics, int pos, int *x, int *y)
{
	int		i;

	i = 0;
	*y = 2;
	*x = 3;
	while (i < pos && *y < graphics->y - 2)
	{
		*x = 3;
		while (*x < graphics->arenax - 3 && i < pos)
		{
			*x += 1;
			if ((i + 1) % 2 == 0)
				*x += 1;
			i += 1;
		}
		if (i != pos)
			*y += 1;
	}
}

void	vis_print_cursor(t_graphics *graphics, t_cursor *cursor, int pos)
{
	int x;
	int y;

	x = 0;
	y = 0;
	cursor = NULL;
	if (pos < 0 || pos >= MEM_SIZE)
		return ;
	vis_calc_pos(graphics, pos, &x, &y);
	mvwprintw(graphics->arena, y, x, ft_itoa(pos));
	wrefresh(graphics->arena);
}
