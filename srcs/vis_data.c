/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vis_data.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 08:01:52 by lhageman      #+#    #+#                 */
/*   Updated: 2020/07/21 17:34:48 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"
#include <ncurses.h>

void	vis_color(t_vm *vm)
{
	if (vm->last_live == 1)
		wattron(vm->vis->graphics->data, COLOR_PAIR(1));
	if (vm->last_live == 2)
		wattron(vm->vis->graphics->data, COLOR_PAIR(4));
	if (vm->last_live == 3)
		wattron(vm->vis->graphics->data, COLOR_PAIR(7));
	if (vm->last_live == 4)
		wattron(vm->vis->graphics->data, COLOR_PAIR(10));
	wattroff(vm->vis->graphics->data, A_BOLD);
}

void	reset_color(t_vm *vm)
{
	wattron(vm->vis->graphics->data, COLOR_PAIR(15));
	wattron(vm->vis->graphics->data, A_BOLD);
}

int		vis_print_data(t_vm *vm)
{
	char *str;

	reset_color(vm);
	mvwprintw(vm->vis->graphics->data, 3, 4, "CYCLE:");
	mvwprintw(vm->vis->graphics->data, 3, 22, "     ");
	str = ft_itoa(vm->cycle_count);
	mvwprintw(vm->vis->graphics->data, 3, 22, str);
	ft_strdel(&str);
	mvwprintw(vm->vis->graphics->data, 4, 4, "CYCLE_TO_DIE:");
	str = ft_itoa(vm->ctd);
	mvwprintw(vm->vis->graphics->data, 4, 22, str);
	ft_strdel(&str);
	wrefresh(vm->vis->graphics->data);
	mvwprintw(vm->vis->graphics->data, 5, 4, "LAST LIVE PLAYER:");
	str = ft_itoa(vm->last_live);
	vis_color(vm);
	mvwprintw(vm->vis->graphics->data, 5, 22, str);
	ft_strdel(&str);
	wrefresh(vm->vis->graphics->data);
	usleep(20000);
	return (0);
}
