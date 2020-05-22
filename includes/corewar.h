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
//	1 -> invalid option - general
//	2 -> invalid option - player no > MAX_PLAYERS
//	3 -> invalid option - player no already exists

# define OPTIONS	"dnv"

// I think it might be a better solution to have the arena in a simple char* and have a wrapper function that calculates the indices with the offset and a boolian variable for enabling or disabling the l... (lfork, lld, lldi) operations
// typedef struct		s_byte
// {
// 	unsigned char	byte;
// 	struct s_byte	*next;
// 	struct s_byte	*prev;
// }					t_byte;

typedef struct		s_cursor
{
	char			*PC;
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
	header_t		*champions;
	t_cursor		*cursor;
	char			*arena;
	unsigned int	visualizer;
	int				dump;
}					t_vm;

typedef struct		s_op_fct
{
	int				(*f)(t_cursor *cursor);
	t_op			*op_info;
}					t_op_fct;

extern t_op_fct		g_op_fct_tab[17];

int					op_live(t_cursor *cursor);
int					op_ld(t_cursor *cursor);
int					op_st(t_cursor *cursor);
int					op_add(t_cursor *cursor);
int					op_sub(t_cursor *cursor);
int					op_and(t_cursor *cursor);
int					op_or(t_cursor *cursor);
int					op_xor(t_cursor *cursor);
int					op_zjmp(t_cursor *cursor);
int					op_ldi(t_cursor *cursor);
int					op_sti(t_cursor *cursor);
int					op_fork(t_cursor *cursor);
int					op_lld(t_cursor *cursor);
int					op_lldi(t_cursor *cursor);
int					op_lfork(t_cursor *cursor);
int					op_aff(t_cursor *cursor);

int					print_message(int message_code, int fd, int ret);
int					free_vm(t_vm *vm, int ret);
int					input_validation(t_vm *vm, char **argv, int argc);

// int					is_option(char *str);
// int					save_option(char **argv, int argc);

int					is_champion(char **argv, int *champ_len);
int					save_champion(t_vm *vm, char *file, int champ_len, int champ_no);

#endif
