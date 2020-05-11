# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    _files.mk                                          :+:    :+:             #
#                                                      +:+                     #
#    By: mmarcell <mmarcell@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/28 18:56:22 by mmarcell      #+#    #+#                  #
#    Updated: 2020/05/11 14:21:34 by zitzak        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

VM_FILES := some_vm_function.c

ASM_FILES :=	op.c						\
				asm_set_options.c 			\
				asm_get_input_file.c 		\
				asm_tokenize_input.c 		\
				asm_create_output_file.c 	\
				asm_write_translation.c		\
				asm_lexical_analysis.c
