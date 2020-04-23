# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mmarcell <mmarcell@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/08 13:03:52 by mmarcell      #+#    #+#                  #
#    Updated: 2020/04/23 11:40:45 by moana         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include ../srcs/_files
include ./srcs/_test_files

NAME := 

OBJS := $(FILES:%.c=../objs/%.o)
TESTS_OBJS := $(TEST_FILES:%.c=objs/%.o)

CFLAGS := -Wall -Wextra -Werror

LIBFT_PATH := ../libft
LIBFT := $(LIBFT_PATH)/libft.a

INCLUDES_PATH := ../includes
INCLUDES := -I $(INCLUDES_PATH) -I $(LIBFT_PATH)
HDRS := $(INCLUDES_PATH)/

PLUS = \033[38;5;40m+\033[0;00m
MINUS = \033[38;5;160m-\033[0;00m

all: test

# uncomment for linux
test: $(OBJS) $(TESTS_OBJS)
	@$(CC) -o $@ $^ -lcriterion $(LIBFT)
	@echo -e " ${PLUS} $@"

# uncomment for linux
objs/%.o: srcs/%.c $(HDRS) | objs
	@$(CC) -c $(CFLAGS) -o $@ $(INCLUDES) $<
	@echo -e " ${PLUS} $@"

## uncomment for macOS
#test: $(OBJS) $(TESTS_OBJS)
#	@$(CC) -o $@ $^ -lcriterion $(LIBFT)
#	@echo " ${PLUS} $@"
#
## uncomment for macOS
#objs/%.o: srcs/%.c $(HDRS) | objs
#	@$(CC) -c $(CFLAGS) -o $@ $(INCLUDES) $<
#	@echo " ${PLUS} $@"

objs:
	@mkdir -p $@

clean:
	@rm -fv $(TESTS_OBJS) | sed -e $$'s/^/ $(MINUS) /'

fclean: clean
	@rm -fv test | sed -e $$'s/^/ $(MINUS) /'

re: fclean all

.PHONY: all test clean fclean re
