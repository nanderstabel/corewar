/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   corewargraphicdemo.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/17 12:20:07 by lhageman      #+#    #+#                 */
/*   Updated: 2020/05/25 19:35:39 by lhageman      ########   odam.nl         */
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

void	ft_test_print(void)
{
	while (1)
	{
		refresh();									//keeps updating your window
		usleep(DELAY);
		ft_attr_p1(1);
		mvaddstr(1, 3, "11 11 11 11");				//output string on certain x and y
		ft_attr_p1(2);
		mvaddstr(1, 18, "11 11 11 11");
		ft_attr_p1(3);
		mvaddstr(1, 33, "11");
		mvaddstr(1, 36, "11");
		mvaddstr(1, 39, "11");
		mvaddstr(1, 42, "11");
		ft_attr_p2(1);
		mvaddstr(3, 3, "11 11 11 11");
		ft_attr_p2(2);
		mvaddstr(3, 18, "11 11 11 11");
		ft_attr_p2(3);
		mvaddstr(3, 33, "11");
		mvaddstr(3, 36, "11");
		mvaddstr(3, 39, "11");
		mvaddstr(3, 42, "11");
		ft_attr_p3(1);
		mvaddstr(5, 3, "11 11 11 11");
		ft_attr_p3(2);
		mvaddstr(5, 18, "11 11 11 11");
		ft_attr_p3(3);
		mvaddstr(5, 33, "11");
		mvaddstr(5, 36, "11");
		mvaddstr(5, 39, "11");
		mvaddstr(5, 42, "11");
		ft_attr_p4(1);
		mvaddstr(7, 3, "11 11 11 11");
		ft_attr_p4(2);
		mvaddstr(7, 18, "11 11 11 11");
		ft_attr_p4(3);
		mvaddstr(7, 33, "11");
		mvaddstr(7, 36, "11");
		mvaddstr(7, 39, "11");
		mvaddstr(7, 42, "11");
		sleep(3);
		refresh();
		sleep(3);
		attron(COLOR_PAIR(9));
		mvaddstr(0, 0, "This is a demo for Corewar!\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n");
		sleep(2);
	}
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
	sleep(10);
	ft_close_windows(arena, data);
	return (0);
}

int	main(void)
{
	initscr();									//initialize the window
	noecho();									//don't echo any keypresses
	curs_set(FALSE);							//dont display a cursor
	ft_set_pairs();
	// attron(COLOR_PAIR(9));
	// mvaddstr(0, 0, "This is a demo for Corewar!\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n");
	// ft_test_print();
	t_vm vm;
	vm.cycle_count = 0;
	vm.CTD = CYCLE_TO_DIE;
	ft_initiate_arena(&vm);
	sleep(1);
	endwin();
}
