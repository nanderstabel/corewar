/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   corewar.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 11:17:00 by zitzak        #+#    #+#                 */
/*   Updated: 2020/07/13 12:08:12 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdlib.h>
# include "libft.h"
# include "op.h"
# include "cor_errors.h"
# include "vis.h"

# define OPTIONS				"dnv"

# define STDIN					0
# define STDOUT					1
# define STDERR					2
# define REG					1
# define DIR					2
# define IND					3

typedef struct		s_cursor
{
	unsigned int	pc;
	unsigned int	op_code;
	unsigned int	ctw;
	unsigned int	decay;
	int				reg[REG_NUMBER + 1];
	unsigned int	carry;
	int				player;
	struct s_cursor	*next;
}					t_cursor;

typedef struct		s_champ
{
	int				id;
	unsigned char	exec_code[CHAMP_MAX_SIZE];
	t_header		header;
}					t_champ;
typedef struct		s_vis	t_vis;

typedef struct		s_vm
{
	unsigned int	champ_count;
	int				last_live;
	unsigned int	cycle_count;
	unsigned int	total_cycle_count;
	unsigned int	ctd;
	unsigned int	check_count;
	unsigned int	live_count;
	unsigned int	visualizer;
	int				dump;
	t_vis			*vis;
	t_champ			**champ;
	t_cursor		*cursors;
	unsigned char	arena[MEM_SIZE];
}					t_vm;

typedef void		(*t_op_table[17])(t_vm *vm, t_cursor *cursor);

void				op_live(t_vm *vm, t_cursor *cursor);
void				op_ld(t_vm *vm, t_cursor *cursor);
void				op_st(t_vm *vm, t_cursor *cursor);
void				op_add(t_vm *vm, t_cursor *cursor);
void				op_sub(t_vm *vm, t_cursor *cursor);
void				op_and(t_vm *vm, t_cursor *cursor);
void				op_or(t_vm *vm, t_cursor *cursor);
void				op_xor(t_vm *vm, t_cursor *cursor);
void				op_zjmp(t_vm *vm, t_cursor *cursor);
void				op_ldi(t_vm *vm, t_cursor *cursor);
void				op_sti(t_vm *vm, t_cursor *cursor);
void				op_fork(t_vm *vm, t_cursor *cursor);
void				op_lld(t_vm *vm, t_cursor *cursor);
void				op_lldi(t_vm *vm, t_cursor *cursor);
void				op_lfork(t_vm *vm, t_cursor *cursor);
void				op_aff(t_vm *vm, t_cursor *cursor);

int					print_message(char *message, char *info, int fd, \
					int ret);
int					free_vm(t_vm *vm, int ret);
void				cursor_del(t_cursor *cursor);

int					input_validation(t_vm *vm, char **argv, int argc);

int					is_champion(char *file, int *champ_len);
int					read_champion(unsigned char *buf, char *file_name, \
					unsigned int champ_file_size);

int					save_champion(t_vm *vm, char *file, int champ_len, \
					unsigned int champ_no);

int					convert_to_int(unsigned char *start, unsigned int len);
unsigned int		new_idx(unsigned int current_idx, int offset, \
					unsigned int flag);
void				put_arena(unsigned char *arena);
void				put_exec_code(unsigned char *code, unsigned int size);

int					vm_start(t_vm *vm);
int					cursors_init(t_vm *vm);

void				game_loop(t_vm *vm, t_op_table operations);

int					get_arg_type(unsigned char enc, unsigned int no);

void				perform_check(t_vm *vm);
#endif