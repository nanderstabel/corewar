# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mmarcell <mmarcell@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/08 13:03:52 by mmarcell      #+#    #+#                  #
#    Updated: 2020/05/12 18:21:53 by zitzak        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include ../srcs/_files.mk
include ./srcs/_test_files.mk

TEST_MAIN = test_main

TEST_MAIN_FILE = test_main.c

OBJS := $(ASM_FILES:%.c=../objs/%.o) $(VM_FILES:%.c=../objs/%.o)

TESTS_OBJS := $(TEST_FILES:%.c=objs/%.o)

TEST_MAIN_OBJ := $(TEST_MAIN_FILE:%.c=objs/%.o)

CFLAGS := -Wall -Wextra -Werror

LIBFT_PATH := ../libft
LIBFT := $(LIBFT_PATH)/libft.a

INCLUDES_PATH := ../includes
INCLUDES := -I $(INCLUDES_PATH) -I $(LIBFT_PATH)
HDRS := $(INCLUDES_PATH)/

PLUS := $$(tput setaf 2)+$$(tput sgr0)
MINUS := $$(tput setaf 1)-$$(tput sgr0)

all: test

test: $(OBJS) $(TESTS_OBJS)
	@$(CC) -o $@ $^ -lcriterion $(LIBFT)
	@echo " ${PLUS} $@"

objs/%.o: srcs/%.c $(HDRS) | objs
	@$(CC) -c $(CFLAGS) -o $@ $(INCLUDES) $<
	@echo " ${PLUS} $@"

objs:
	@mkdir -p $@

test_main: $(TEST_MAIN_OBJ) $(OBJS)
	@$(CC) -o $(TEST_MAIN) $^ $(INCLUDES) $(LIBFT) $(CFLAGS)
	@./test_main

clean:
	@rm -fv $(TESTS_OBJS) $(TEST_MAIN_OBJ) | sed "s/^/ $(MINUS) /"

fclean: clean
	@rm -fv test test_main | sed "s/^/ $(MINUS) /"

re: fclean all

.PHONY: all test clean fclean re
