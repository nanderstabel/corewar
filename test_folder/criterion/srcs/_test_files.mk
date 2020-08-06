# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    _test_files.mk                                     :+:    :+:             #
#                                                      +:+                     #
#    By: mmarcell <mmarcell@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/28 18:56:18 by mmarcell      #+#    #+#                  #
#    Updated: 2020/07/26 11:10:00 by nstabel       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

COR_TEST_FILES :=					\
	test_cor_input.c				\
	test_cor_vm_helpers.c			\
	test_cor_op_helpers.c			\
	test_cor_op_st.c				\
	test_cor_op_ld.c				\
	test_cor_op_ldi.c				\
	test_cor_op_sti.c				\
	test_cor_op_live.c
	
ASM_TEST_FILES := 					\
	test_get_input_file.c			\
	test_analyze_lexicon.c			\
	test_syntax_analysis.c			\
	test_instruction_analysis.c		\
	test_parameter_analysis.c		\
	test_translate_to_bytecode.c	\
	test_label_check.c
