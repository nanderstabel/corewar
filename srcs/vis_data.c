/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vis_data.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 08:01:52 by lhageman      #+#    #+#                 */
/*   Updated: 2020/08/07 10:17:21 by lhageman      ########   odam.nl         */
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

void	vis_print_line(WINDOW *data, int y, int x, int nbr)
{
	char *str;

	str = ft_itoa(nbr);
	mvwprintw(data, y, x, "      ");
	mvwprintw(data, y, x, str);
	ft_strdel(&str);
}

void	vis_print_players(t_vm *vm, int y)
{
	unsigned int	i;
	char			*name;

	i = 1;
	while (i <= vm->champ_count)
	{
		vm->vis->attr[i](vis_calc_att(false, false), vm->vis->graphics->data);
		mvwprintw(vm->vis->graphics->data, y + i, 4, "PLAYER ");
		vis_print_line(vm->vis->graphics->data, y + i, 11, i);
		y += 1;
		name = ft_strsub(vm->champ[i]->header.prog_name, 0, 50);
		mvwprintw(vm->vis->graphics->data, y + i, 4, name);
		ft_strdel(&name);
		y += 1;
		name = ft_strsub(vm->champ[i]->header.prog_name, 50, 50);
		mvwprintw(vm->vis->graphics->data, y + i, 4, name);
		ft_strdel(&name);
		y += 1;
		name = ft_strsub(vm->champ[i]->header.prog_name, 100, 28);
		mvwprintw(vm->vis->graphics->data, y + i, 4, name);
		ft_strdel(&name);
		y += 1;
		i += 1;
	}
}

int		vis_print_data(t_vm *vm)
{
	reset_color(vm);
	mvwprintw(vm->vis->graphics->data, 3, 4, "TOTAL CYLES:");
	vis_print_line(vm->vis->graphics->data, 3, 22, vm->total_cycle_count);
	mvwprintw(vm->vis->graphics->data, 4, 4, "CYCLES TO DIE:");
	vis_print_line(vm->vis->graphics->data, 4, 22, vm->ctd);
	mvwprintw(vm->vis->graphics->data, 5, 4, "CYCLE DELTA:");
	vis_print_line(vm->vis->graphics->data, 5, 22, CYCLE_DELTA);
	mvwprintw(vm->vis->graphics->data, 6, 4, "LIVE REPORTS:");
	vis_print_line(vm->vis->graphics->data, 6, 22, vm->live_count);
	mvwprintw(vm->vis->graphics->data, 7, 4, "NBR LIVE:");
	vis_print_line(vm->vis->graphics->data, 7, 22, NBR_LIVE);
	mvwprintw(vm->vis->graphics->data, 8, 4, "WINNING PLAYER:");
	vis_color(vm);
	vis_print_line(vm->vis->graphics->data, 8, 22, vm->last_live);
	vis_print_players(vm, 10);
	wrefresh(vm->vis->graphics->data);
	return (0);
}
