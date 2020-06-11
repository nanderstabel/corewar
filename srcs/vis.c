/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vis.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 09:53:39 by lhageman      #+#    #+#                 */
/*   Updated: 2020/06/11 10:47:21 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

int		vis_close_windows(t_vis *vis)
{
	delwin(vis->graphics->data);
	delwin(vis->graphics->arena);
	endwin();
	return (0);
}

void	vis_set_graphics(t_graphics *graphics)
{
	graphics->arena = newwin(VIS_Y, ARENA_X, 0, 0);
	graphics->data = newwin(VIS_Y, DATA_X, 0, ARENA_X);
}

void	vis_set(t_vis *vis)
{
	vis->graphics = ft_memalloc(sizeof(t_graphics));
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
	initscr();
	noecho();
	curs_set(FALSE);
	vis_set_pairs();
}

void	vis_create(t_vm *vm)
{
	vis_initiate();
	vis_set(vm->vis);
	vis_initiate_arena(vm);
}
