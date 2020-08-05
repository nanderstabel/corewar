/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vis_cursor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 09:43:31 by lhageman      #+#    #+#                 */
/*   Updated: 2020/08/01 14:15:03 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

void	vis_attr_array(t_attr_func *attr)
{
	attr[0] = NULL;
	attr[1] = vis_attr_p1;
	attr[2] = vis_attr_p2;
	attr[3] = vis_attr_p3;
	attr[4] = vis_attr_p4;
}

void	vis_calc_pos(int pos, int *x, int *y)
{
	int		i;

	i = 0;
	*y = 2;
	*x = 3;
	while (i < pos)
	{
		*x = 3;
		while (*x < ARENA_X - 3 && i < pos)
		{
			*x += 3;
			i += 1;
		}
		if (i != pos)
		{
			*y += 1;
			if (*y == VIS_Y - 2)
				*y = 2;
		}
	}
}

int		vis_calc_att(int bold, int inverse)
{
	if (bold == 1 && inverse == 0)
		return (2);
	if (bold == 0 && inverse == 1)
		return (3);
	if (bold == 1 && inverse == 1)
		return (4);
	else
		return (1);
}

void	vis_print(t_vis *vis, int x, int y)
{
	unsigned int	i;
	char			*c;

	i = 0;
	while (i < vis->bytes)
	{
		while (x < ARENA_X - 3 && i < vis->bytes)
		{
			if (vis->index + i >= MEM_SIZE)
			{
				vis->bytes = vis->bytes - i;
				vis->index = 0;
				i = 0;
				x = 3;
				y = 2;
			}
			c = vis_itoa(vis->arena[vis->index + i]);
			mvwprintw(vis->graphics->arena, y, x, c);
			ft_strdel(&c);
			x += 3;
			i += 1;
		}
		y += 1;
		x = 3;
	}
	wrefresh(vis->graphics->arena);
}

void	vis_print_cursor(t_vis *vis)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (vis == NULL)
		return ;
	if (vis->index >= MEM_SIZE)
		return ;
	if (vis->index == 0)
	{
		x = 3;
		y = 2;
	}
	else
		vis_calc_pos(vis->index, &x, &y);
	vis_print(vis, x, y);
}
