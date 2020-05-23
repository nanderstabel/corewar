/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   corewargraphicdemo.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/17 12:20:07 by lhageman      #+#    #+#                 */
/*   Updated: 2020/05/20 16:24:43 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "ft_graphics.h"

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

int	main(int argc, char *argv[])
{
	initscr();									//initialize the window
	noecho();									//don't echo any keypresses
	curs_set(FALSE);							//dont display a cursor
	ft_set_pairs();
	attron(COLOR_PAIR(9));
	mvaddstr(0, 0, "This is a demo for Corewar!\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n");
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
	sleep(1);
	endwin();
}
