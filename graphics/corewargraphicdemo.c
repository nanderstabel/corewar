/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   corewargraphicdemo.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/17 12:20:07 by lhageman      #+#    #+#                 */
/*   Updated: 2020/06/05 11:26:39 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

int		ft_close_windows(t_graphics *graphics)
{
	delwin(graphics->data);
	delwin(graphics->arena);
	return (0);
}

void	vis_set_graphics(t_graphics *graphics)
{
	graphics->arena = newwin(VIS_Y, ARENA_X, 0, 0);
	graphics->data = newwin(VIS_Y, DATA_X, 0, ARENA_X);
}

void	vis_set(t_vis *vis)
{
	vis_set_graphics(vis->graphics);
	vis_attr_array(vis->attr);
	vis->arena = NULL;
	vis->index = 0;
	vis->bytes = 0;
	vis->player = 0;
	vis->bold = 0;
	vis->inverse = 0;
}

void	vis_initiate(void)
{
	initscr();									//initialize the window
	noecho();									//don't echo any keypresses
	curs_set(FALSE);							//dont display a cursor
	ft_set_pairs();								//set color pairs
}

int		main(void)
{
	t_vis	vis;
	t_vm	vm;

	vis_initiate();
	vis_set(&vis);
	vm.cycle_count = 0;
	vm.ctd = CYCLE_TO_DIE;
	ft_initiate_arena(&vis, &vm);
	mvwprintw(vis.graphics->data, 8, 4, "ending window");
	wrefresh(vis.graphics->data);
	sleep(2);
	ft_close_windows(vis.graphics);
	sleep(2);
	endwin();
	return (0);
}
