/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 11:17:00 by zitzak        #+#    #+#                 */
/*   Updated: 2020/07/10 12:03:11 by zitzak        ########   odam.nl         */
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
# define LABEL_ERR				"No such label %s while attempting to dereference token [TOKEN]"

# define ERROR_FORMAT			"[%3.3u:%3.3u] %s \"%s\"\n"
# define STRING_FORMAT			"[%3.3u:%3.3u] %s \"\"%s\"\"\n"
# define ENDLINE_FORMAT			"[%3.3u:%3.3u] %s\n"
# define LEXICAL_ERR			"Lexical error at [%d:%d]\n"
# define END_LABEL_CHARS		",%#\";\n \t\v\f\0"
# define WHITESPACES			" \t\v\f"
# define DIGITS_INDIRECT		"-0123456789"

# define TWO_DIGITS				2
# define LOOK_UP_LEVELS			9

enum
{
	DEBUG_O = (1 << 0),
	USAGE_O = (1 << 1),
	DEBUG_L = (1 << 2)
}	e_flags;

enum
{
	INITIALIZE_OPT,
	READ_ARGUMENT_OPT,
	FIND_DASH_OPT,
	FIND_OPTION_OPT,
	VALIDATE_ARGUMENT_OPT,
	PRINT_USAGE_MESSAGE_OPT,
	UNINSTALL_OPT
}	e_state_opt;

enum
{
	INITIALIZE,
	SET_OPTIONS,
	GET_INPUT_FILE,
	ANALYZE_LEXICON,
	ANALYZE_SYNTAX,
	ANALYZE_PARAMETERS,
	ANALYZE_INSTRUCTIONS,
	CREATE_OUTPUT_FILE,
	TRANSLATE_TO_BYTE,
	BYTECODE_TO_FILE,
	FREE_PROJECT,
	UNINSTALL
}	e_state;

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

typedef struct		s_token
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
	char			*og_line;
	char			comment_found;
	char			header_found;
	char			opcode_temp;
	size_t			pc;
	size_t			temp_addres;
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

typedef struct		s_redirect
{
	char			*chars;
	t_f				func;
}					t_redirect;

typedef struct		s_token_tab
{
	char			*string;
	char			*lower;
	char			size;
	unsigned char	code;
	t_event			translate;
	char			next[END + 1];
}					t_token_tab;

extern t_token_tab	g_token_tab[END + 1];

t_bool				set_options(t_project *as);
t_bool				get_input_file(t_project *as);
t_bool				analyze_lexicon(t_project *as);
t_bool				analyze_syntax(t_project *as);
t_bool				analyze_parameters(t_project *as);
t_bool				analyze_instructions(t_project *as);
t_bool				create_output_file(t_project *as);
t_bool				translate_to_byte(t_project *as);
t_bool				bytecode_to_file(t_project *as);
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
t_bool				translate_argument(t_project *as);
t_bool				translate_instruction(t_project *as);
t_bool				translate_label(t_project *as);
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

void				write_str_to_buf(t_project *as, char *to_bytecode,
					char type);
void				write_byte_to_buf(t_project *as, char byte);
void				add_buffer_to_list(t_project *as);
t_bool				byte_string_to_file(t_project *as, int type,
					size_t max_size);
void				print_zero_bytes(t_project *as, size_t len,
					size_t max_size);
t_bool				check_str_to_long(int type, size_t max_size, size_t len);
t_bool				byte_num_to_file(t_project *as, int num);
void				add_strings(t_project *as, char **line);

#endif
