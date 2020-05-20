/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   corewar.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 11:17:00 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/20 11:30:59 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "op.h"

//TODO create error enum so exit_with_message can print the right message given
//its first param. 
//	0 -> usage
//	1 -> no message (because error message has been printed already)

# define ERROR		0
# define SUCCESS	1

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
	int				color;
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
	unsigned 		dump;
}					t_vm;

typedef struct		s_op_fct
{
	int				(*f)(t_cursor *cursor);
	t_op			*op_info;
}					t_op_fct;

extern t_op_fct		op_fct_tab[17];

int			op_live(t_cursor *cursor);
int			op_ld(t_cursor *cursor);
int			op_st(t_cursor *cursor);
int			op_add(t_cursor *cursor);
int			op_sub(t_cursor *cursor);
int			op_and(t_cursor *cursor);
int			op_or(t_cursor *cursor);
int			op_xor(t_cursor *cursor);
int			op_zjmp(t_cursor *cursor);
int			op_ldi(t_cursor *cursor);
int			op_sti(t_cursor *cursor);
int			op_fork(t_cursor *cursor);
int			op_lld(t_cursor *cursor);
int			op_lldi(t_cursor *cursor);
int			op_lfork(t_cursor *cursor);
int			op_aff(t_cursor *cursor);

int			exit_with_message(t_vm *vm, int message_code, int fd, int ret);
int			input_validation(t_vm *vm);
#endif