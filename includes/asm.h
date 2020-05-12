/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 11:17:00 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/12 20:33:22 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"

# define OPTIONS				"agu"
# define SYNTAX_ERR				"Syntax error at token [TOKEN]"
# define INSTRUCTION_ERR		"Invalid instruction at token [TOKEN]"

# define ERROR_FORMAT			"[%3.3u:%3.3u] %s \"%s\"\n"

typedef t_bool				(*t_f)(t_project *, char**);

enum
{
	DEBUG_O = (1 << 0),
	USAGE_O = (1 << 1)
}	e_flags;

enum
{
	INDIRECT_LABEL,
	LABEL,
	INSTRUCTION,
	REGISTER,
	SEPARATOR,
	DIRECT_LABEL,
	DIRECT,
	COMMAND_NAME,
	COMMAND_COMMENT,
	STRING,
	ENDLINE,
	INDIRECT,
	END
}	e_token;

typedef struct s_token
{
	size_t			row;
	size_t			column;
	short			token_type;
	char			*literal_str;
	struct s_token	*next;
}					t_token;

typedef struct		s_project
{
	int				count;
	size_t			row;
	size_t			column;
	int				fd;
	int				argc;
	char			**argv;
	int				flags;
	size_t			index;
	char			*string;
	t_hash_table	*labels;
	t_list			*token_list;
	t_list			*tmp;
	t_token			*current_token;
	t_token			*next_token;
}					t_project;

typedef struct s_redirect
{
	char		*chars;
	t_f			func;
}				t_redirect;

typedef struct		s_token_tab
{
	char			*string;
	char			next[END + 1];
}					t_token_tab;

extern t_token_tab	token_tab[END + 1];

t_bool				set_options(t_project *as);
t_bool				get_input_file(t_project *as);
t_bool				analyze_lexicon(t_project *as);
t_bool				tokenize_input(t_project *as);
t_bool				analyze_syntax(t_project *as);
t_bool				analyze_parameters(t_project *as);
t_bool				analyze_instructions(t_project *as);
t_bool				create_output_file(t_project *as);
t_bool				translate_to_byte(t_project *as);
t_bool				write_translation(t_project *as);
t_bool				lexical_analysis(t_machine *as);
t_bool				print_usage_message(t_project *as);
t_bool				skip_whitespaces(t_project *as, char **line);
t_bool				process_line(t_project *as, char **line);
t_bool				skip_comment_line(t_project *as, char **line);
t_bool				direct_token(t_project *as, char **line);
t_bool				direct_label_token(t_project *as, char **line);
t_bool				command_token(t_project *as, char **line);
t_token				*new_token(t_project *as, short type, char *str);
t_bool				loop_token_list(t_project *as, \
					t_bool (*check)(t_project *as));

#endif
