/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_graphics.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhageman <lhageman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 14:16:44 by lhageman      #+#    #+#                 */
/*   Updated: 2020/05/25 20:06:12 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GRAPHICS_H
# define FT_GRAPHICS_H

# include <ncurses.h>
# include <unistd.h>

# define ANSI_WHEAT 229
# define ANSI_ETON_BLUE 71
# define ANSI_OCEAN_GREEN 25
# define ANSI_COPPER 130
# define ANSI_GREY 8
# define DELAY 30000
# define COLOR_PLAYER_ONE ANSI_COPPER
# define COLOR_PLAYER_TWO ANSI_ETON_BLUE
# define COLOR_PLAYER_THREE ANSI_OCEAN_GREEN
# define COLOR_PLAYER_FOUR ANSI_WHEAT

void	ft_attr_p1(int set, WINDOW *arena);
void	ft_attr_p2(int set, WINDOW *arena);
void	ft_attr_p3(int set, WINDOW *arena);
void	ft_attr_p4(int set, WINDOW *arena);

#endif
