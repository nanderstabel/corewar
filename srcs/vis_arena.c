/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vis_arena.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 16:31:49 by lhageman      #+#    #+#                 */
/*   Updated: 2020/07/06 17:41:30 by lhageman      ########   odam.nl         */
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

int		vis_draw_arena(t_graphics *graphics)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	y = 2;
	wattron(graphics->arena, COLOR_PAIR(9));
	while (i < MEM_SIZE && y < VIS_Y - 2)
	{
		x = 3;
		while (x < ARENA_X - 3 && i < MEM_SIZE)
		{
			mvwprintw(graphics->arena, y, x, "0");
			x += 1;
			mvwprintw(graphics->arena, y, x, "0");
			x += 2;
			i += 1;
		}
		y += 1;
	}
	wrefresh(graphics->arena);
	return (0);
}

int		vis_initiate_arena(t_vm *vm)
{
	// char		arena[MEM_SIZE];
	// int			i;

	vis_draw_borders(vm->vis->graphics);
	vis_print_data(vm);
	vm->vis->arena = vm->arena;
	// i = 0;
	// while (i < MEM_SIZE)
	// {
	// 	arena[i] = '0';
	// 	i += 1;
	// }
	vis_draw_arena(vm->vis->graphics);
	vis_print_cursor(vm->vis);
	return (0);
}
