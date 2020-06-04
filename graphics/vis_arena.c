/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vis_arena.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 16:31:49 by lhageman      #+#    #+#                 */
/*   Updated: 2020/06/04 09:59:17 by lhageman      ########   odam.nl         */
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
	vis_borders(graphics->arena, graphics->y, graphics->arenax);
	vis_borders(graphics->data, graphics->y, graphics->datax);
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
	while (i < MEM_SIZE && y < graphics->y - 2)
	{
		x = 3;
		while (x < graphics->arenax - 3 && i < MEM_SIZE)
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

int		ft_initiate_arena(t_graphics *graphics, t_vm *vm)
{
	int			data_size;
	char		*arena;
	t_cursor	*cursor;
	int			i;

	data_size = 5;
	graphics->x = 192 + 57 + 6;
	graphics->y = 37;
	graphics->arenax = 192 + 6;
	graphics->datax = 57;
	graphics->arena = newwin(graphics->y, graphics->arenax, 0, 0);
	graphics->data = newwin(graphics->y, graphics->datax, 0, graphics->arenax);
	draw_borders(graphics);
	ft_print_data(graphics, vm);
	arena = ft_memalloc(MEM_SIZE);
	i = 0;
	while (i < MEM_SIZE)
	{
		arena[i] = '0';
		i += 1;
	}
	draw_arena(graphics, arena);
	sleep(2);
	vis_print_players(graphics);
	cursor = NULL;
	vis_print_cursor(graphics, cursor, 3);
	sleep(20);
	ft_close_windows(graphics);
	return (0);
}
