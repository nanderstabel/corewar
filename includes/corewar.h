/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   corewar.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 11:17:00 by zitzak        #+#    #+#                 */
/*   Updated: 2020/08/08 10:47:12 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdlib.h>
# include "libft.h"
# include "op.h"
# include "cor_errors.h"
# include "vis.h"

# define OPTIONS		"abcdefnv"

# define FORMAT_A		"P%5i | %s"
# define FORMAT_F		"Player %i (%s) is said to be alive\n"

# define STDIN			0
# define STDOUT			1
# define STDERR			2
# define REG			REG_CODE
# define DIR			DIR_CODE
# define IND			IND_CODE

typedef struct		s_cursor
{
	unsigned int	pc;
	unsigned int	op_code;
	unsigned int	ctw;
	unsigned int	decay;
	int				reg[REG_NUMBER + 1];
	unsigned int	carry;
	int				player;
	int				p;
	struct s_cursor	*next;
}					t_cursor;

typedef struct		s_champ
{
	int				id;
	unsigned char	exec_code[CHAMP_MAX_SIZE];
	t_header		header;
}					t_champ;

typedef struct s_vis	t_vis;

typedef struct		s_vm
{
	unsigned int	champ_count;
	int				last_live;
	unsigned int	cycle_count;
	unsigned int	total_cycle_count;
	int				ctd;
	unsigned int	check_count;
	unsigned int	live_count;
	unsigned int	a_option;
	char			*a_string;
	unsigned int	b_option;
	unsigned int	c_option;
	unsigned int	e_option;
	unsigned int	f_option;
	unsigned int	visualizer;
	int				dump;
	t_vis			*vis;
	t_champ			**champ;
	t_cursor		*cursors;
	size_t			cursor_count;
	unsigned char	arena[MEM_SIZE];
}					t_vm;

typedef void	(*t_op_table[17])(t_vm *vm, t_cursor *cursor);

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

int					print_message(char *message, char *info, int fd);
int					print_usage(int ret);
int					free_vm(t_vm *vm);
void				cursor_del(t_cursor *cursor);

int					input_validation(t_vm *vm, char **argv, int argc);

int					save_option(t_vm *vm, char **argv, int idx, int argc);

int					is_champion(char *file, int *champ_len);
int					read_champion(unsigned char *buf, char *file_name, \
					unsigned int champ_file_size);

int					save_champion(t_vm *vm, char *file, int champ_len, \
					unsigned int champ_no);

int					convert_to_int(unsigned char *arena, unsigned int idx, \
					unsigned int len);
unsigned int		new_idx(unsigned int current_idx, int offset, \
					unsigned int flag);
void				put_arena(unsigned char *arena);
void				put_exec_code(unsigned char *code, unsigned int size);
void				print_pc(t_vm *vm, t_cursor *cursor, size_t size);

int					vm_start(t_vm *vm);
int					cursors_init(t_vm *vm);

void				game_loop(t_vm *vm, t_op_table operations);
void				put_adv(t_vm *vm, t_cursor *cursor, size_t size);

int					get_arg_type(unsigned char enc, unsigned int no);
void				store_in_arena(unsigned char *arena, unsigned int idx, \
					unsigned int len, int value);
int					get_value(t_vm *vm, t_cursor *cursor, int param[4]);

void				perform_check(t_vm *vm);

#endif
