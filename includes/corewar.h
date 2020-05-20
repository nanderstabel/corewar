/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   corewar.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 11:17:00 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/20 11:40:22 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

#include "libft.h"
#include "op.h"

typedef struct		s_byte
{
	unsigned char	byte	: 8;
	struct s_byte	*next;
	struct s_byte	*prev;
}					t_byte;

typedef struct		s_cursor
{
	t_byte			*PC;
	unsigned int	CTW;
	unsigned int	decay;
	int				*reg[REG_NUMBER];
	unsigned int	carry;
	char            *color;
}					t_cursor;

typedef struct		s_vm
{
	unsigned int	champ_count;
	int				last_live;
	unsigned int	cycle_count; 
	unsigned int	total_cycle_count;
	unsigned int	CTD;
	unsigned int	check_count;
	unsigned int	live_count;
	header_t    	*champions;
	t_cursor    	*cursor;
	t_byte			*first_byte;
	int				options;
	unsigned 		dump:
}					t_vm;

typedef struct		op_fct
{
	int				(*f)(t_byte *pos, );
};

void				some_vm_function(char *s);

#endif