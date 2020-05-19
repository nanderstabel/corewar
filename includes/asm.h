/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 11:17:00 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/19 22:10:39 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */



#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"

# define OPTIONS				"agul"
# define SYNTAX_ERR				"Syntax error at token [TOKEN]"
# define UNEXPECTED_END			"Syntax error - unexpected end of input (Perhaps you forgot to end with a newline ?)\n"
# define INSTRUCTION_ERR		"Invalid instruction at token [TOKEN]"

# define ERROR_FORMAT			"[%3.3u:%3.3u] %s \"%s\"\n"
# define ENDLINE_FORMAT			"[%3.3u:%3.3u] %s\n"
# define LEXICAL_ERR			"Lexical error at [%d:%d]\n"
# define END_LABEL_CHARS		",%#\";\n \t\v\f\0"
# define WHITESPACES			" \t\v\f"
# define DIGITS_INDIRECT		"-0123456789"

# define TWO_DIGITS				2
# define LOOK_UP_LEVELS			9

typedef t_bool				(*t_f)(t_project *, char**);

enum
{
	DEBUG_O = (1 << 0),
	USAGE_O = (1 << 1),
	DEBUG_L = (1 << 2)
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
	char			opcode;
	unsigned char	encoding;
	char			size;
	short			token_type;
	short			address;
	char			*literal_str;
}					t_token;

typedef struct		s_project
{
	int				count;
	size_t			row;
	size_t			column;
	int				fd;
	int				argc;
	char			**argv;
	char			name_found;
	char			comment_found;
	char			header_found;
	char			opcode_temp;
	size_t			pc;
	int				flags;
	size_t			index;
	char			*string;
	t_arg_type		octal;
	char			*temp;
	char			*buffer;
	t_hash_table	*labels;
	size_t			n_labels;
	t_list			*token_list;
	t_list			*tmp;
	t_list			*trail;
	t_list			*bytecode_list;
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
	char			*lower;
	char			size;
	unsigned char	code;
	t_event			translate;
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
t_bool				free_project(t_project *as);
t_bool				lexical_analysis(t_machine *as);
t_bool				print_usage_message(t_project *as);
t_bool				skip_whitespaces(t_project *as, char **line);
t_bool				process_line(t_project *as, char **line);
t_bool				skip_comment_line(t_project *as, char **line);
t_bool				direct_token(t_project *as, char **line);
t_bool				direct_label_token(t_project *as, char **line);
t_bool				command_token(t_project *as, char **line);
t_token				*new_token(t_project *as, size_t y_axis, \
					short type, char *str);
t_bool				loop_token_list(t_project *as, \
					t_bool (*check)(t_project *as));
t_bool				translate_indirect_label(t_project *as);
t_bool				translate_instruction(t_project *as);
t_bool				translate_register(t_project *as);
t_bool				translate_direct_label(t_project *as);
t_bool				translate_direct(t_project *as);
t_bool				translate_indirect(t_project *as);
void				increment_line(t_project *as, char **line, size_t len);
t_bool				is_valid_label_chars(t_project *as, char **line);
void				skip_to_end_number(t_project *as, char **line);
t_bool				indirect_label_token(t_project *as, char **line);
t_bool				label_or_instruction_token(t_project *as, char **line);
t_bool				register_token(t_project *as, char **line);
t_bool				label_chars_redirect(t_project *as, char **line);
t_bool				indrect_token(t_project *as, char **line);	
t_bool				separator_token(t_project *as, char **line);
t_bool				string_token(t_project *as, char **line);
int					add_to_string_token(t_project *as, char **line);
int					new_string_token(t_project *as, char **line);
void				endline_token(t_project *as, char **line);
void				end_token(t_project *as);
void				instruction_token(t_project *as, char **line);
void				label_token(t_project *as, char **line);

void				*label_columns(t_hash_table *table);
t_bool				syntax_check(t_project *as);
t_bool				is_argument(char token);
char				*label_to_key(char *str, char token);
t_bool				parameter_check(t_project *as);
t_bool				del_token_node(t_project *as);
t_bool				del_token_list(t_project *as);
t_bool				get_argtype(t_project *as);

void				write_str_to_buf(t_project *as, char *to_bytecode, char type);
void				write_byte_to_buf(t_project *as, char byte);
void				add_buffer_to_list(t_project *as);

#endif
