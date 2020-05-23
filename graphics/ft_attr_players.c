/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_attr_players.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 16:24:05 by lhageman      #+#    #+#                 */
/*   Updated: 2020/05/20 16:25:46 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graphics.h"

void	ft_attr_p1(int set)
{
	if (set == 1 || set == 2)
	{
		attron(COLOR_PAIR(1));
		if (set == 2)
			attron(A_BOLD);
		else
			attroff(A_BOLD);
	}
	if (set == 3)
	{
		attron(COLOR_PAIR(2));
		attroff(A_BOLD);
	}
}

void	ft_attr_p2(int set)
{
	if (set == 1 || set == 2)
	{
		attron(COLOR_PAIR(3));
		if (set == 2)
			attron(A_BOLD);
		else
			attroff(A_BOLD);
	}
	if (set == 3)
	{
		attron(COLOR_PAIR(4));
		attroff(A_BOLD);
	}
}

void	ft_attr_p3(int set)
{
	if (set == 1 || set == 2)
	{
		attron(COLOR_PAIR(5));
		if (set == 2)
			attron(A_BOLD);
		else
			attroff(A_BOLD);
	}
	if (set == 3)
	{
		attron(COLOR_PAIR(6));
		attroff(A_BOLD);
	}
}

void	ft_attr_p4(int set)
{
	if (set == 1 || set == 2)
	{
		attron(COLOR_PAIR(7));
		if (set == 2)
			attron(A_BOLD);
		else
			attroff(A_BOLD);
	}
	if (set == 3)
	{
		attron(COLOR_PAIR(8));
		attroff(A_BOLD);
	}
}
