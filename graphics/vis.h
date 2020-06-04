/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vis.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 14:16:44 by lhageman      #+#    #+#                 */
/*   Updated: 2020/06/04 09:58:31 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_H
# define VIS_H

# include <ncurses.h>
# include <unistd.h>
# include "../includes/corewar.h"
# include "../includes/op.h"

# define ANSI_WHEAT 229
# define ANSI_ETON_BLUE 71
# define ANSI_OCEAN_GREEN 25
# define ANSI_COPPER 130
# define ANSI_GREY 8
# define ANSI_PINK 109
# define DELAY 30000
# define COLOR_PLAYER_ONE ANSI_COPPER
# define COLOR_PLAYER_TWO ANSI_ETON_BLUE
# define COLOR_PLAYER_THREE ANSI_OCEAN_GREEN
# define COLOR_PLAYER_FOUR ANSI_WHEAT

typedef struct	s_graphics
{
	WINDOW		*arena;
	WINDOW		*data;
	int			x;
	int			y;
	int			arenax;
	int			datax;
}				t_graphics;

void			ft_attr_p1(int set, WINDOW *arena);
void			ft_attr_p2(int set, WINDOW *arena);
void			ft_attr_p3(int set, WINDOW *arena);
void			ft_attr_p4(int set, WINDOW *arena);

void			ft_set_pairs(void);
int				ft_initiate_arena(t_graphics *graphics, t_vm *vm);
int				ft_close_windows(t_graphics *graphics);

void			vis_print_cursor(t_graphics *graphics,\
				t_cursor *cursor, int pos);

#endif
