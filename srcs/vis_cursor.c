/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vis_cursor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 09:43:31 by lhageman      #+#    #+#                 */
/*   Updated: 2020/08/08 11:53:34 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

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
	if (*x >= ARENA_X - 3)
	{
		*x = 3;
		*y += 1;
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

void	vis_print_str(t_vis *vis, int y, int x, int i)
{
	char	*c;

	c = vis_itoa(vis->arena[vis->index + i]);
	mvwprintw(vis->graphics->arena, y, x, c);
	ft_strdel(&c);
}

void	vis_print(t_vis *vis, int x, int y)
{
	unsigned int	i;

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
			vis_print_str(vis, y, x, i);
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
