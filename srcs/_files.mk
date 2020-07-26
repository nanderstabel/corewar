# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    _files.mk                                          :+:    :+:             #
#                                                      +:+                     #
#    By: mmarcell <mmarcell@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/28 18:56:22 by mmarcell      #+#    #+#                  #
#    Updated: 2020/07/26 10:52:09 by nstabel       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

COR_FILES :=					\
	op.c						\
	cor_input.c					\
	cor_input_save_option.c		\
	cor_input_check_file.c		\
	cor_input_add_champion.c	\
	cor_exit.c					\
	cor_vm_helpers.c			\
	cor_vm_start.c				\
	cor_vm_game.c				\
	cor_vm_check.c				\
	cor_op_add.c				\
	cor_op_aff.c				\
	cor_op_and.c				\
	cor_op_fork.c				\
	cor_op_ld.c					\
	cor_op_ldi.c				\
	cor_op_lfork.c				\
	cor_op_live.c				\
	cor_op_lld.c				\
	cor_op_lldi.c				\
	cor_op_or.c					\
	cor_op_st.c					\
	cor_op_sti.c				\
	cor_op_sub.c				\
	cor_op_xor.c				\
	cor_op_zjmp.c				\
	cor_op_helpers.c			\
	vis_arena.c					\
	vis_attr_players.c			\
	vis_cursor.c				\
	vis_data.c					\
	vis.c						\
	vis_helpers.c

ASM_FILES :=					\
	op.c						\
	asm_token_tab.c				\
	asm_loop_token_list.c		\
	asm_set_options.c			\
	asm_get_input_file.c		\
	asm_analyze_lexicon.c		\
	asm_analyze_syntax.c		\
	asm_analyze_parameters.c	\
	asm_analyze_instructions.c	\
	asm_create_output_file.c	\
	asm_free_project.c			\
	asm_translate_to_byte.c		\
	asm_bytecode_to_file.c		\
	asm_is_argument.c			\
	asm_label_to_key.c			\
	asm_label_columns.c			\
	asm_get_argtype.c
