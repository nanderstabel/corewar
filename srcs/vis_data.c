/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vis_data.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 08:01:52 by lhageman      #+#    #+#                 */
/*   Updated: 2020/08/01 14:42:54 by lhageman      ########   odam.nl         */
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

void	vis_print_players(t_vm *vm)
{
	unsigned int i;
	int j;
	int y;
	char *name;

	i = 1;
	y = 8;
	while (i <= vm->champ_count)
	{
		vm->vis->attr[i](vis_calc_att(false, false), vm->vis->graphics->data);
		j = 0;
		name = ft_strsub(vm->champ[i]->header.prog_name, 0, 50);
		mvwprintw(vm->vis->graphics->data, y + i, 4, name);
		free(name);
		y += 1;
		name = ft_strsub(vm->champ[i]->header.prog_name, 50, 50);
		mvwprintw(vm->vis->graphics->data, y + i, 4, name);
		free(name);
		y += 1;
		name = ft_strsub(vm->champ[i]->header.prog_name, 100, 28);
		mvwprintw(vm->vis->graphics->data, y + i, 4, name);
		free(name);
		y += 1;
		i += 1;
	}
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
	mvwprintw(vm->vis->graphics->data, 4, 4, "CHECKS TOTAL");
	str = ft_itoa(vm->check_count);
	mvwprintw(vm->vis->graphics->data, 4, 22, str);
	ft_strdel(&str);
	mvwprintw(vm->vis->graphics->data, 5, 4, "CYCLES TO DIE");
	str = ft_itoa(vm->ctd);
	mvwprintw(vm->vis->graphics->data, 5, 22, str);
	ft_strdel(&str);
	mvwprintw(vm->vis->graphics->data, 6, 4, "LAST LIVE PLAYER:");
	str = ft_itoa(vm->last_live);
	vis_color(vm);
	mvwprintw(vm->vis->graphics->data, 6, 22, str);
	ft_strdel(&str);
	vis_print_players(vm);
	wrefresh(vm->vis->graphics->data);
	usleep(5000);
	return (0);
}
