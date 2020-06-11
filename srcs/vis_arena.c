/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vis_arena.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 16:31:49 by lhageman      #+#    #+#                 */
/*   Updated: 2020/06/11 10:57:44 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

void	vis_borders(WINDOW *window, int y, int x)
{
	int i;

	i = 0;
	wattron(window, COLOR_PAIR(10));
	while (i < x)
	{
		mvwprintw(window, 0, i, "*");
		mvwprintw(window, y - 1, i, "*");
		i += 1;
	}
	i = 0;
	while (i < y)
	{
		mvwprintw(window, i, 0, "*");
		mvwprintw(window, i, x - 1, "*");
		i += 1;
	}
	wrefresh(window);
	wattroff(window, COLOR_PAIR(10));
}

void	vis_draw_borders(t_graphics *graphics)
{
	vis_borders(graphics->arena, VIS_Y, ARENA_X);
	vis_borders(graphics->data, VIS_Y, DATA_X);
}

int		vis_draw_arena(t_graphics *graphics, char *arena)
{
	int		i;
	int		x;
	int		y;
	char	c[2];

	i = 0;
	y = 2;
	wattron(graphics->arena, COLOR_PAIR(9));
	while (i < MEM_SIZE && y < VIS_Y - 2)
	{
		x = 3;
		while (x < ARENA_X - 3 && i < MEM_SIZE)
		{
			c[0] = arena[i];
			c[1] = '\0';
			mvwprintw(graphics->arena, y, x, c);
			x += 1;
			if ((i + 1) % 2 == 0)
				x += 1;
			i += 1;
		}
		y += 1;
	}
	wrefresh(graphics->arena);
	return (0);
}

int		vis_initiate_arena(t_vm *vm)
{
	char		arena[MEM_SIZE];
	int			i;

	vis_draw_borders(vm->vis->graphics);
	vis_print_data(vm);
	i = 0;
	while (i < MEM_SIZE)
	{
		arena[i] = '0';
		i += 1;
	}
	vis_draw_arena(vm->vis->graphics, arena);
	vis_print_cursor(vm->vis);
	return (0);
}
