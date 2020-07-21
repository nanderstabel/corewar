/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vis_attr_players.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 16:24:05 by lhageman      #+#    #+#                 */
/*   Updated: 2020/07/21 11:50:35 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

void	vis_set_pairs(void)
{
	start_color();
	init_pair(1, ANSI_COPPER, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, ANSI_COPPER);
	init_pair(11, COLOR_WHITE, ANSI_COPPER);
	init_pair(3, ANSI_ETON_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, ANSI_ETON_BLUE);
	init_pair(12, COLOR_WHITE, ANSI_ETON_BLUE);
	init_pair(5, ANSI_OCEAN_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, ANSI_OCEAN_GREEN);
	init_pair(13, COLOR_WHITE, ANSI_OCEAN_GREEN);
	init_pair(7, ANSI_WHEAT, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, ANSI_WHEAT);
	init_pair(14, COLOR_WHITE, ANSI_WHEAT);
	init_pair(9, ANSI_GREY, COLOR_BLACK);
	init_pair(10, ANSI_PINK, ANSI_PINK);
}

void	vis_attr_p1(int set, WINDOW *arena)
{
	if (set == 1 || set == 2)
	{
		wattron(arena, COLOR_PAIR(1));
		if (set == 2)
			wattron(arena, A_BOLD);
	}
	if (set == 3)
		wattron(arena, COLOR_PAIR(2));
	if (set == 4)
		wattron(arena, COLOR_PAIR(11));
	if (set == 1 || set == 3 || set == 4)
		wattroff(arena, A_BOLD);
}

void	vis_attr_p2(int set, WINDOW *arena)
{
	if (set == 1 || set == 2)
	{
		wattron(arena, COLOR_PAIR(3));
		if (set == 2)
			wattron(arena, A_BOLD);
	}
	if (set == 3)
		wattron(arena, COLOR_PAIR(4));
	if (set == 4)
		wattron(arena, COLOR_PAIR(12));
	if (set == 1 || set == 3 || set == 4)
		wattroff(arena, A_BOLD);
}

void	vis_attr_p3(int set, WINDOW *arena)
{
	if (set == 1 || set == 2)
	{
		wattron(arena, COLOR_PAIR(5));
		if (set == 2)
			wattron(arena, A_BOLD);
	}
	if (set == 3)
		wattron(arena, COLOR_PAIR(6));
	if (set == 4)
		wattron(arena, COLOR_PAIR(13));
	if (set == 1 || set == 3 || set == 4)
		wattroff(arena, A_BOLD);
}

void	vis_attr_p4(int set, WINDOW *arena)
{
	if (set == 1 || set == 2)
	{
		wattron(arena, COLOR_PAIR(7));
		if (set == 2)
			wattron(arena, A_BOLD);
	}
	if (set == 3)
		wattron(arena, COLOR_PAIR(8));
	if (set == 4)
		wattron(arena, COLOR_PAIR(14));
	if (set == 1 || set == 3 || set == 4)
		watroff(arena, A_BOLD);
}
