/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vis_data.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 08:01:52 by lhageman      #+#    #+#                 */
/*   Updated: 2020/06/11 10:40:43 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

int		vis_print_data(t_vm *vm)
{
	char *str;

	mvwprintw(vm->vis->graphics->data, 3, 4, "CYCLE:");
	str = ft_itoa(vm->cycle_count);
	mvwprintw(vm->vis->graphics->data, 3, 20, str);
	ft_strdel(&str);
	mvwprintw(vm->vis->graphics->data, 4, 4, "CYCLE_TO_DIE:");
	str = ft_itoa(vm->ctd);
	mvwprintw(vm->vis->graphics->data, 4, 20, str);
	ft_strdel(&str);
	wrefresh(vm->vis->graphics->data);
	return (0);
}
