/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: zaz <marvin@42.fr>                           +#+                     */
/*                                                   +#+                      */
/*   Created: 2013/10/04 11:33:27 by zaz           #+#    #+#                 */
/*   Updated: 2020/07/10 16:59:42 by lhageman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
**
** All sizes are in bytes.
** We assume that an int is 32 bits. Is this true for you?
*/

#ifndef OP_H
# define OP_H

# include <stdlib.h>

# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define MAX_ARGS_NUMBER	4
# define MAX_PLAYERS		4
# define MEM_SIZE			4096
# define IDX_MOD			512
# define CHAMP_MAX_SIZE		MEM_SIZE / 6
//TODO check if 4096 / 6 = 682 or 4096 / 6 = 683

# define COMMENT_CHAR		'#'
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','

# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define REG_NUMBER			16

# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10

/*
**
*/

typedef char		t_arg_type;

# define T_REG				1
# define T_DIR				2
# define T_IND				4
# define T_LAB				8

/*
**
*/

# define PROG_NAME_LENGTH		128
# define NAME_LEN				PROG_NAME_LENGTH
# define COMMENT_LENGTH			2048
# define COM_LEN				COMMENT_LENGTH
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}					t_header;

typedef struct		s_op
{
	char			*operation;
	size_t			n_args;
	t_arg_type		args[3];
	char			opcode;
	short			cycles_to_wait;
	char			*description;
	char			encoded;
	char			label;
}					t_op;

extern t_op			g_op_tab[17];

#endif
