/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vis_data.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 08:01:52 by lhageman      #+#    #+#                 */
/*   Updated: 2020/06/11 09:48:35 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

int		vis_print_data(t_vis *vis, t_vm *vm)
{
	char *str;

	mvwprintw(vis->graphics->data, 3, 4, "CYLE:");
	str = ft_itoa(vm->cycle_count);
	mvwprintw(vis->graphics->data, 3, 20, str);
	ft_strdel(&str);
	mvwprintw(vis->graphics->data, 4, 4, "CYCLE_TO_DIE:");
	str = ft_itoa(vm->ctd);
	mvwprintw(vis->graphics->data, 4, 20, str);
	ft_strdel(&str);
	wrefresh(vis->graphics->data);
	return (0);
}
