/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   corewargraphicdemo.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/17 12:20:07 by lhageman      #+#    #+#                 */
/*   Updated: 2020/05/27 11:00:19 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graphics.h"

void	ft_set_pairs(void)
{
	start_color();
	init_pair(1, ANSI_COPPER, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, ANSI_COPPER);
	init_pair(3, ANSI_ETON_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, ANSI_ETON_BLUE);
	init_pair(5, ANSI_OCEAN_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, ANSI_OCEAN_GREEN);
	init_pair(7, ANSI_WHEAT, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, ANSI_WHEAT);
	init_pair(9, ANSI_GREY, COLOR_BLACK);
}

void	draw_borders(WINDOW *screen, int y, int x)
{
	int i;

	i = 1;
	// 4 corners 
	// mvwprintw(screen, 0, 0, "+"); 
	// mvwprintw(screen, y - 1, 0, "+"); 
	// mvwprintw(screen, 0, x - 1, "+"); 
	// mvwprintw(screen, y - 1, x - 1, "+"); 
	// sides 
	// for (i = 1; i < (y - 1); i++) 
	// { 
	// 	mvwprintw(screen, i, 0, "|"); 
	// 	mvwprintw(screen, i, x - 1, "|"); 
	// } // top and bottom 
	while (i < (x - 1))
	{
		mvwprintw(screen, 0, i, "-");
		i += 1;
		// mvwprintw(screen, y - 1, i, "-"); 
	}
}

int	ft_close_windows(t_graphics *graphics)
{
	delwin(graphics->arena);
	delwin(graphics->data);
	return (0);
}

int	ft_print_data(t_graphics *graphics, t_vm *vm)
{
	char *str;

	werase(graphics->data);
	draw_borders(graphics->data, graphics->y, graphics->x);
	mvwprintw(graphics->data, 1, 1, "CYLE:");
	str = ft_itoa(vm->cycle_count);
	mvwprintw(graphics->data, 1, 16, str);
	ft_strdel(&str);
	mvwprintw(graphics->data, 2, 1, "CYCLE_TO_DIE:");
	str = ft_itoa(vm->CTD);
	mvwprintw(graphics->data, 2, 16, str);
	ft_strdel(&str);
	wrefresh(graphics->data);
	return (0);
}

int		ft_set_arena(t_graphics *graphics)
{
	int		data_size;
	int		i;
	int		x;
	int		y;

	werase(graphics->arena);
	getmaxyx(stdscr, graphics->y, graphics->x);
	data_size = 5;
	x = 1;
	y = 3;
	i = 0;
	wattron(graphics->arena, COLOR_PAIR(9));
	while (i < MEM_SIZE && y < graphics->y - data_size - 3)
	{
		while (x < graphics->x - 1)
		{
			mvwprintw(graphics->arena, y, x, "0");
			x += 1;
			if (x % 3 == 0)
				x += 1;
			i += 1;
		}
		x = 1;
		y += 1;
	}
	wrefresh(graphics->arena);
	return (0);
}

int	ft_initiate_arena(t_graphics *graphics, t_vm *vm)
{
	int		data_size;

	data_size = 5;
	getmaxyx(stdscr, graphics->y, graphics->x);
	graphics->arena = newwin(graphics->y - data_size, graphics->x, 0, 0);
	graphics->data = newwin(data_size, graphics->x, graphics->y - data_size, 0);
	draw_borders(graphics->data, graphics->y, graphics->x);
	mvwprintw(graphics->arena, 1, 1, "I AM THE ARENA");
	mvwprintw(graphics->data, 1, 1, "I AM DATA");
	wrefresh(graphics->arena);
	wrefresh(graphics->data);
	sleep(5);
	ft_print_data(graphics, vm);
	ft_set_arena(graphics);
	sleep(10);
	ft_close_windows(graphics);
	return (0);
}

int		main(void)
{
	t_vm		vm;
	t_graphics	graphics;

	initscr();									//initialize the window
	noecho();									//don't echo any keypresses
	curs_set(FALSE);							//dont display a cursor
	ft_set_pairs();								//set color pairs
	vm.cycle_count = 0;
	vm.CTD = CYCLE_TO_DIE;
	ft_initiate_arena(&graphics, &vm);
	sleep(1);
	endwin();
}
