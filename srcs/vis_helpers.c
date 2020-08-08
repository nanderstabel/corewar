/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vis_helpers.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 15:47:10 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/08/08 11:54:02 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"
#include "corewar.h"

int		vis_calc_inch(t_vm *vm)
{
	int		i;
	int		c;
	int		x;
	int		y;
	chtype	attr;

	i = 0;
	c = 0;
	x = 3;
	y = 2;
	vis_calc_pos(vm->vis->index, &x, &y);
	attr = mvwinch(vm->vis->graphics->arena, y, x);
	while (i <= 15)
	{
		if ((attr & A_COLOR) == COLOR_PAIR(i))
			c = i;
		i += 1;
	}
	if (c == 0)
		c = 13;
	return (c);
}

char	*vis_itoa(unsigned char nbr)
{
	char	*result;

	result = ft_strnew(2);
	if (nbr < 15)
		result[0] = '0';
	else
	{
		if (nbr / 16 < 10)
			result[0] = '0' + nbr / 16;
		else
			result[0] = 'a' + nbr / 16 - 10;
	}
	if (nbr % 16 < 10)
		result[1] = '0' + nbr % 16;
	else
		result[1] = 'a' + nbr % 16 - 10;
	return (result);
}

void	vis_exit(t_vm *vm)
{
	if (vm->vis == NULL)
		return ;
	vis_close_windows(vm->vis);
	if (vm->vis->graphics)
	{
		ft_bzero(vm->vis->graphics, sizeof(t_graphics));
		ft_memdel((void**)&(vm->vis->graphics));
	}
	ft_bzero(vm->vis, sizeof(t_vis));
	ft_memdel((void**)&(vm->vis));
}
