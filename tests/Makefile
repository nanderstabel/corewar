# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mmarcell <mmarcell@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/08 13:03:52 by mmarcell      #+#    #+#                  #
#    Updated: 2020/07/12 14:34:39 by lhageman      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include ../srcs/_files.mk
include ./srcs/_test_files.mk

COR_TEST_NAME := cor_test
ASM_TEST_NAME := asm_test

COR_OBJS := $(COR_FILES:%.c=../objs/%.o)
ASM_OBJS := $(ASM_FILES:%.c=../objs/%.o)
COR_TEST_OBJS := $(COR_TEST_FILES:%.c=objs/%.o)
ASM_TEST_OBJS := $(ASM_TEST_FILES:%.c=objs/%.o)
TEST_OBJS := COR_TEST_OBJS ASM_TEST_OBJS

CFLAGS := -Wall -Wextra -Werror -lncurses
TEST_MAIN = test_main

TEST_MAIN_FILE = test_main.c

TESTS_OBJS := $(TEST_FILES:%.c=objs/%.o)

TEST_MAIN_OBJ := $(TEST_MAIN_FILE:%.c=objs/%.o)

LIBFT_PATH := ../libft
LIBFT := $(LIBFT_PATH)/libft.a

INCLUDES_PATH := ../includes
INCLUDES := -I $(INCLUDES_PATH) -I $(LIBFT_PATH)
HDRS := $(INCLUDES_PATH)/

PLUS := $$(tput setaf 2)+$$(tput sgr0)
MINUS := $$(tput setaf 1)-$$(tput sgr0)

all: cor_test asm_test

cor_test: $(COR_OBJS) $(COR_TEST_OBJS)
	@$(CC) -o $@ $^ $(CFLAGS) -lcriterion $(LIBFT)
	@echo " ${PLUS} $@"

asm_test: $(ASM_OBJS) $(ASM_TEST_OBJS)
	@$(CC) -o $@ $^ $(CFLAGS) -lcriterion $(LIBFT)
	@echo " ${PLUS} $@"

objs/%.o: srcs/%.c $(HDRS) | objs
	@$(CC) -c $(CFLAGS) -o $@ $(INCLUDES) $<
	@echo " ${PLUS} $@"

objs:
	@mkdir -p $@

test_main: $(TEST_MAIN_OBJ) $(OBJS)
	@$(CC) -o $(TEST_MAIN) $^ $(INCLUDES) $(LIBFT) $(CFLAGS) -g

clean:
	@rm -rfv objs | sed "s/^/ $(MINUS) /"

fclean: clean
	@rm -fv test test_main | sed "s/^/ $(MINUS) /"

re: fclean all

.PHONY: all test clean fclean re
