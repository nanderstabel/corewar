# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    _files.mk                                          :+:    :+:             #
#                                                      +:+                     #
#    By: mmarcell <mmarcell@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/28 18:56:22 by mmarcell      #+#    #+#                  #
#    Updated: 2020/07/09 18:48:42 by zitzak        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


VM_FILES := some_vm_function.c

ASM_FILES :=	op.c						\
				asm_token_tab.c				\
				asm_loop_token_list.c		\
				asm_set_options.c 			\
				asm_get_input_file.c 		\
				asm_analyze_lexicon.c 		\
				asm_analyze_syntax.c 		\
				asm_analyze_parameters.c 	\
				asm_analyze_instructions.c 	\
				asm_create_output_file.c 	\
				asm_write_translation.c		\
				asm_free_project.c			\
				asm_translate_to_byte.c 	\
				asm_write_translation.c		\
				asm_is_argument.c			\
				asm_label_to_key.c			\
				asm_label_columns.c			\
				asm_get_argtype.c
