/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   corewargraphicdemo.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/17 12:20:07 by lhageman      #+#    #+#                 */
/*   Updated: 2020/05/25 20:17:25 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "ft_graphics.h"
#include "../includes/corewar.h"
#include "../includes/op.h"

void	ft_set_pairs()
{
	start_color();	
	init_pair(1, ANSI_COPPER, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, ANSI_COPPER);		
	init_pair(3, ANSI_ETON_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, ANSI_ETON_BLUE);							//start the color
	init_pair(5, ANSI_OCEAN_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, ANSI_OCEAN_GREEN);
	init_pair(7, ANSI_WHEAT, COLOR_BLACK);		//assign a new pair of fg and bg color to an init pair
	init_pair(8, COLOR_BLACK, ANSI_WHEAT);
	init_pair(9, ANSI_GREY, COLOR_BLACK);
}

void draw_borders(WINDOW *screen) 
{ 
	int x, y, i; getmaxyx(screen, y, x); 
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
	for (i = 1; i < (x - 1); i++) 
	{ 
		mvwprintw(screen, 0, i, "-"); 
		// mvwprintw(screen, y - 1, i, "-"); 
	} 
}

int	ft_close_windows(WINDOW *arena, WINDOW *data)
{
	delwin(arena);
	delwin(data);
	return (0);
}

int	ft_print_data(WINDOW *data, t_vm *vm)
{
	char *str;

	werase(data);
	draw_borders(data);
	mvwprintw(data, 1, 1, "CYLE:");
	str = ft_itoa(vm->cycle_count);
	mvwprintw(data, 1, 16, str);
	ft_strdel(&str);
	mvwprintw(data, 2, 1, "CYCLE_TO_DIE:");
	str = ft_itoa(vm->CTD);
	mvwprintw(data, 2, 16, str);
	ft_strdel(&str);
	wrefresh(data);
	return (0);
}

int	ft_set_arena(WINDOW *arena)
{
	int		parent_x;
	int		parent_y;
	int		data_size;
	int		i;
	int		x;
	int		y;

	werase(arena);
	getmaxyx(stdscr, parent_y, parent_x);
	data_size = 5;
	x = 1;
	y = 3;
	i = 0;
	wattron(arena, COLOR_PAIR(9));
	while (i < MEM_SIZE && y < parent_y - data_size - 3)
	{
		while (x < parent_x - 1)
		{
			mvwprintw(arena, y, x, "0");
			x += 1;
			if (x % 3 == 0)
				x += 1;
			i += 1;
		}
		x = 1;
		y += 1;
	}
	wrefresh(arena);
	return (0);
}

int	ft_initiate_arena(t_vm *vm)
{
	int		parent_x;
	int		parent_y;
	int		data_size;
	WINDOW	*arena;
	WINDOW	*data;

	data_size = 5;
	getmaxyx(stdscr, parent_y, parent_x);
	arena = newwin(parent_y - data_size, parent_x, 0, 0);
	data = newwin(data_size, parent_x, parent_y - data_size, 0);
	draw_borders(data);
	sleep(2);
	mvwprintw(arena, 1, 1, "I AM THE ARENA");
	mvwprintw(data, 1, 1, "I AM DATA");
	wrefresh(arena);
	wrefresh(data);
	sleep(2);
	ft_print_data(data, vm);
	ft_set_arena(arena);
	sleep(10);
	ft_close_windows(arena, data);
	return (0);
}

int	main(void)
{
	initscr();									//initialize the window
	noecho();									//don't echo any keypresses
	curs_set(FALSE);							//dont display a cursor
	ft_set_pairs();								//set color pairs
	t_vm vm;
	vm.cycle_count = 0;
	vm.CTD = CYCLE_TO_DIE;
	ft_initiate_arena(&vm);
	sleep(1);
	endwin();
}
