/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_attr_players.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 16:24:05 by lhageman      #+#    #+#                 */
/*   Updated: 2020/05/25 20:05:01 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graphics.h"

void	ft_attr_p1(int set, WINDOW *arena)
{
	if (set == 1 || set == 2)
	{
		wattron(arena, COLOR_PAIR(1));
		if (set == 2)
			wattron(arena, A_BOLD);
		else
			wattroff(arena, A_BOLD);
	}
	if (set == 3)
	{
		wattron(arena, COLOR_PAIR(2));
		wattroff(arena, A_BOLD);
	}
}

void	ft_attr_p2(int set, WINDOW *arena)
{
	if (set == 1 || set == 2)
	{
		wattron(arena, COLOR_PAIR(3));
		if (set == 2)
			wattron(arena, A_BOLD);
		else
			wattroff(arena, A_BOLD);
	}
	if (set == 3)
	{
		wattron(arena, COLOR_PAIR(4));
		wattroff(arena, A_BOLD);
	}
}

void	ft_attr_p3(int set, WINDOW *arena)
{
	if (set == 1 || set == 2)
	{
		wattron(arena, COLOR_PAIR(5));
		if (set == 2)
			wattron(arena, A_BOLD);
		else
			wattroff(arena, A_BOLD);
	}
	if (set == 3)
	{
		wattron(arena, COLOR_PAIR(6));
		wattroff(arena, A_BOLD);
	}
}

void	ft_attr_p4(int set, WINDOW *arena)
{
	if (set == 1 || set == 2)
	{
		wattron(arena, COLOR_PAIR(7));
		if (set == 2)
			wattron(arena, A_BOLD);
		else
			wattroff(arena, A_BOLD);
	}
	if (set == 3)
	{
		wattron(arena, COLOR_PAIR(8));
		wattroff(arena, A_BOLD);
	}
}
