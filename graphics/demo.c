/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   demo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/17 11:55:20 by lhageman      #+#    #+#                 */
/*   Updated: 2020/05/25 14:05:37 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <ncurses.h>
// #include <unistd.h>

// #define DELAY 30000

// int	main(int argc, char *argv[])
// {
// 	int x;
// 	int y;
// 	int max_y;
// 	int max_x;
// 	int next_x;
// 	int direction;

// 	x = 0;
// 	y = 0;
// 	max_x = 0;
// 	max_y = 0;
// 	next_x = 0;
// 	direction = 1;
// 	initscr();
// 	noecho();
// 	curs_set(FALSE);
// 	getmaxyx(stdscr, max_y, max_x);
// 	while (1)
// 	{
// 		getmaxyx(stdscr, max_y, max_x);
// 		clear();
// 		mvprintw(y, x, "o");
// 		refresh();
// 		usleep(DELAY);
// 		next_x = x + direction;
// 		if (next_x >= max_x || next_x < 0)
// 			direction *= -1;
// 		else
// 			x += direction;
// 	}
// 	endwin();
// }

// demo.c 
#include <ncurses.h> 
#include <unistd.h> 

void draw_borders(WINDOW *screen) 
{ 
	int x, y, i; getmaxyx(screen, y, x); 
	// 4 corners 
	mvwprintw(screen, 0, 0, "+"); 
	mvwprintw(screen, y - 1, 0, "+"); 
	mvwprintw(screen, 0, x - 1, "+"); 
	mvwprintw(screen, y - 1, x - 1, "+"); 
	// sides 
	for (i = 1; i < (y - 1); i++) 
	{ 
		mvwprintw(screen, i, 0, "|"); 
		mvwprintw(screen, i, x - 1, "|"); 
	} // top and bottom 
	for (i = 1; i < (x - 1); i++) 
	{ 
		mvwprintw(screen, 0, i, "-"); 
		mvwprintw(screen, y - 1, i, "-"); 
	} 
}


int main(int argc, char *argv[]) 
{
	int parent_x, parent_y, new_x, new_y;
	int score_size = 3;
	initscr();
	noecho();
	curs_set(FALSE);
	// get our maximum window dimensions 
	getmaxyx(stdscr, parent_y, parent_x);
	// set up initial windows 
	WINDOW *field = newwin(parent_y - score_size, parent_x, 0, 0);
	WINDOW *score = newwin(score_size, parent_x, parent_y - score_size, 0);
	// draw to our windows 
	mvwprintw(field, 0, 0, "Field");
	mvwprintw(score, 0, 0, "Score");
	// refresh each window 
	wrefresh(field);
	wrefresh(score);
	// draw our borders 
	draw_borders(field);
	draw_borders(score);
	// simulate the game loop 
	while (1)
	{
		getmaxyx(stdscr, new_y, new_x);
		if (new_y != parent_y || new_x != parent_x)
		{
			parent_x = new_x;
			parent_y = new_y;
			wresize(field, new_y - score_size, new_x);
			wresize(score, score_size, new_x);
			mvwin(score, new_y - score_size, 0);
			wclear(stdscr);
			wclear(field);
			wclear(score);
			draw_borders(field);
			draw_borders(score);
		}
		// draw to our windows 
		mvwprintw(field, 1, 1, "Field");
		mvwprintw(score, 1, 1, "Score");
		// refresh each window
		wrefresh(field);
		wrefresh(score);
	}
	delwin(field);
	delwin(score);
	endwin();
	return 0;
}