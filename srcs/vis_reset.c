/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vis_reset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 17:20:53 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/07/22 17:20:53 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

void	vis_reset_add(t_vis *vis, unsigned char player, unsigned int pos, \
		unsigned int len)
{
	unsigned int idx;

	while (len > 0)
	{
		idx = new_idx(pos, len - 1, TRUE);
		vis->reset[idx].player = player;
		vis->reset[idx].wait = 42;
		--len;
	}
}

void	vis_reset_byte_color(t_vis *vis, unsigned int idx)
{
	vis->attr[vis->reset[idx].player](vis_calc_att(FALSE, FALSE), \
		vis->graphics->arena);
	vis->index = idx;
	vis->bytes = 1;
	vis_print_cursor(vis);
	vis->reset[idx].player = 0;
	vis->reset[idx].wait = 0;
}
