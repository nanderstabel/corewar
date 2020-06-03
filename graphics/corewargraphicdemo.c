/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   corewargraphicdemo.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/17 12:20:07 by lhageman      #+#    #+#                 */
/*   Updated: 2020/06/03 16:37:02 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

int	ft_close_windows(t_graphics *graphics)
{
	delwin(graphics->arena);
	delwin(graphics->data);
	return (0);
}

int		main(void)
{
	t_vm		vm;
	t_graphics	graphics;

	initscr();									//initialize the window
	noecho();									//don't echo any keypresses
	curs_set(FALSE);							//dont display a cursor
	ft_set_pairs();								//set color pairs
	vm.cycle_count = 0;
	vm.ctd = CYCLE_TO_DIE;
	ft_initiate_arena(&graphics, &vm);
	sleep(1);
	endwin();
}
