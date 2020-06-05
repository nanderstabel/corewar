/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vis_arena.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 16:31:49 by lhageman      #+#    #+#                 */
/*   Updated: 2020/06/05 11:23:55 by lhageman      ########   odam.nl         */
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

void	draw_borders(t_graphics *graphics)
{
	vis_borders(graphics->arena, VIS_Y, ARENA_X);
	vis_borders(graphics->data, VIS_Y, DATA_X);
}

int		ft_print_data(t_graphics *graphics, t_vm *vm)
{
	char *str;

	mvwprintw(graphics->data, 3, 4, "CYLE:");
	str = ft_itoa(vm->cycle_count);
	mvwprintw(graphics->data, 3, 20, str);
	ft_strdel(&str);
	mvwprintw(graphics->data, 4, 4, "CYCLE_TO_DIE:");
	str = ft_itoa(vm->ctd);
	mvwprintw(graphics->data, 4, 20, str);
	ft_strdel(&str);
	wrefresh(graphics->data);
	return (0);
}

int		draw_arena(t_graphics *graphics, char *arena)
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

void	vis_print_players(t_graphics *graphics)
{
	wattron(graphics->arena, COLOR_PAIR(2));
	mvwprintw(graphics->arena, 4, 3, "ab");
	mvwprintw(graphics->arena, 4, 6, "cd");
	mvwprintw(graphics->arena, 4, 9, "ef");
	mvwprintw(graphics->arena, 4, 12, "gh");
	mvwprintw(graphics->arena, 4, 15, "ij");
	mvwprintw(graphics->arena, 4, 18, "kl");
	wattroff(graphics->arena, COLOR_PAIR(2));
	wattron(graphics->arena, COLOR_PAIR(4));
	mvwprintw(graphics->arena, 6, 3, "ab");
	mvwprintw(graphics->arena, 6, 6, "cd");
	mvwprintw(graphics->arena, 6, 9, "ef");
	mvwprintw(graphics->arena, 6, 12, "gh");
	mvwprintw(graphics->arena, 6, 15, "ij");
	mvwprintw(graphics->arena, 6, 18, "kl");
	wattroff(graphics->arena, COLOR_PAIR(4));
	wattron(graphics->arena, COLOR_PAIR(6));
	mvwprintw(graphics->arena, 8, 3, "ab");
	mvwprintw(graphics->arena, 8, 6, "cd");
	mvwprintw(graphics->arena, 8, 9, "ef");
	mvwprintw(graphics->arena, 8, 12, "gh");
	mvwprintw(graphics->arena, 8, 15, "ij");
	mvwprintw(graphics->arena, 8, 18, "kl");
	wattroff(graphics->arena, COLOR_PAIR(6));
	wattron(graphics->arena, COLOR_PAIR(8));
	mvwprintw(graphics->arena, 10, 3, "ab");
	mvwprintw(graphics->arena, 10, 6, "cd");
	mvwprintw(graphics->arena, 10, 9, "ef");
	mvwprintw(graphics->arena, 10, 12, "gh");
	mvwprintw(graphics->arena, 10, 15, "ij");
	mvwprintw(graphics->arena, 10, 18, "kl");
	wattroff(graphics->arena, COLOR_PAIR(8));
	wrefresh(graphics->arena);
}

int		ft_initiate_arena(t_vis *vis, t_vm *vm)
{
	char		*arena;
	int			i;

	draw_borders(vis->graphics);
	ft_print_data(vis->graphics, vm);
	arena = ft_memalloc(MEM_SIZE);
	i = 0;
	while (i < MEM_SIZE)
	{
		arena[i] = '0';
		i += 1;
	}
	draw_arena(vis->graphics, arena);
	sleep(2);
	vis->index = 3;
	vis->bytes = 4;
	arena[3] = '1';
	arena[4] = '2';
	arena[5] = '3';
	arena[6] = '4';
	arena[7] = '5';
	arena[8] = '6';
	arena[9] = '7';
	vis->arena = arena;
	vis_print_players(vis->graphics);
	vis_print_cursor(vis);
	sleep(5);
	return (0);
}
