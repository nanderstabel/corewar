/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   demo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/17 11:55:20 by lhageman      #+#    #+#                 */
/*   Updated: 2020/05/18 14:33:20 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000

int	main(int argc, char *argv[])
{
	int x;
	int y;
	int max_y;
	int max_x;
	int next_x;
	int direction;

	x = 0;
	y = 0;
	max_x = 0;
	max_y = 0;
	next_x = 0;
	direction = 1;
	initscr();
	noecho();
	curs_set(FALSE);
	getmaxyx(stdscr, max_y, max_x);
	while (1)
	{
		getmaxyx(stdscr, max_y, max_x);
		clear();
		mvprintw(y, x, "o");
		refresh();
		usleep(DELAY);
		next_x = x + direction;
		if (next_x >= max_x || next_x < 0)
			direction *= -1;
		else
			x += direction;
	}
	endwin();
}
