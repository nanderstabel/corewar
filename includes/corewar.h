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
# include "cor_errors.h"

# define OPTIONS				"dnv"

# define STDIN					0
# define STDOUT					1
# define STDERR					2

// I think it might be a better solution to have the arena in a simple char* and have a wrapper function that calculates the indices with the offset and a boolian variable for enabling or disabling the l... (lfork, lld, lldi) operations
// typedef struct		s_byte
// {
// 	unsigned char	byte;
// 	struct s_byte	*next;
// 	struct s_byte	*prev;
// }					t_byte;

typedef struct		s_cursor
{
	int				pc;
	unsigned int	ctw;
	unsigned int	decay;
	int				*reg[REG_NUMBER];
	unsigned int	carry;
	int				back_to_normal;
	int				color;
}					t_cursor;

typedef struct		s_vm
{
	unsigned int	champ_count;
	int				last_live;
	unsigned int	cycle_count;
	unsigned int	total_cycle_count;
	unsigned int	ctd;
	unsigned int	check_count;
	unsigned int	live_count;
	t_header		**champions;
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

int					op_live(t_vm *vm, t_cursor *cursor);
int					op_ld(t_vm *vm, t_cursor *cursor);
int					op_st(t_vm *vm, t_cursor *cursor);
int					op_add(t_vm *vm, t_cursor *cursor);
int					op_sub(t_vm *vm, t_cursor *cursor);
int					op_and(t_vm *vm, t_cursor *cursor);
int					op_or(t_vm *vm, t_cursor *cursor);
int					op_xor(t_vm *vm, t_cursor *cursor);
int					op_zjmp(t_vm *vm, t_cursor *cursor);
int					op_ldi(t_vm *vm, t_cursor *cursor);
int					op_sti(t_vm *vm, t_cursor *cursor);
int					op_fork(t_vm *vm, t_cursor *cursor);
int					op_lld(t_vm *vm, t_cursor *cursor);
int					op_lldi(t_vm *vm, t_cursor *cursor);
int					op_lfork(t_vm *vm, t_cursor *cursor);
int					op_aff(t_vm *vm, t_cursor *cursor);

int					print_message(char *message, char *info, int fd, \
					int ret);
int					free_vm(t_vm *vm, int ret);
int					input_validation(t_vm *vm, char **argv, int argc);

int					is_champion(char *file, int *champ_len);
int					convert_to_int(char *start, int len);
int					read_champion(char *buf, char *file_name, \
					unsigned int champ_file_size);

int					save_champion(t_vm *vm, char *file, int champ_len, \
					unsigned int champ_no);

unsigned int		new_idx(unsigned int current_idx, int offset, \
					unsigned int flag);
#endif
