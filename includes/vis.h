/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vis.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 14:16:44 by lhageman      #+#    #+#                 */
/*   Updated: 2020/07/21 18:26:53 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_H
# define VIS_H

# include <ncurses.h>
# include <unistd.h>
# include "corewar.h"
# include "op.h"

# define ANSI_WHEAT 229
# define ANSI_ETON_BLUE 71
# define ANSI_OCEAN_GREEN 25
# define ANSI_COPPER 130
# define ANSI_GREY 8
# define ANSI_PINK 109
# define DELAY 30000
# define COLOR_PLAYER_ONE 0
# define COLOR_PLAYER_TWO 1
# define COLOR_PLAYER_THREE 2
# define COLOR_PLAYER_FOUR 3
# define VIS_X 255
# define VIS_Y 74
# define ARENA_X 198
# define DATA_X 57

typedef struct		s_graphics
{
	WINDOW			*arena;
	WINDOW			*data;
}					t_graphics;

typedef void		(*t_attr_func)(int, WINDOW *);
typedef struct		s_vis
{
	t_graphics		*graphics;
	t_attr_func		attr[5];
	unsigned char	*arena;
	unsigned int	index;
	unsigned int	bytes;
}					t_vis;
typedef struct s_vm	t_vm;

void				vis_attr_p1(int set, WINDOW *arena);
void				vis_attr_p2(int set, WINDOW *arena);
void				vis_attr_p3(int set, WINDOW *arena);
void				vis_attr_p4(int set, WINDOW *arena);

void				vis_create(t_vm *vm);
void				vis_set_pairs(void);
int					vis_initiate_arena(t_vm *vm);
int					vis_close_windows(t_vis *vis);

void				vis_print_cursor(t_vis *vis);
int					vis_calc_att(int bold, int inverse);
int					vis_print_data(t_vm *vm);
void				vis_attr_array(t_attr_func *attr);

char				*vis_itoa(unsigned char nbr);
#endif
