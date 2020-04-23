# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mmarcell <mmarcell@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/02/14 13:21:34 by mmarcell      #+#    #+#                  #
#    Updated: 2020/04/22 17:32:25 by moana         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include srcs/_file_names

NAME := libft.a

OBJS := $(FILES:%.c=objs/%.o)

CFLAGS := -Wall -Wextra -Werror

HDRS_PATH := .
INCLUDES := -I $(HDRS_PATH)
HDRS := $(HDRS_PATH)/libft.h

PLUS = \033[0;32m+\033[0;00m
MINUS = \033[0;31m-\033[0;00m

all: $(NAME)

# uncomment for linux
$(NAME): $(OBJS)
	@ar -rcs $(NAME) $^
	@echo -e " ${PLUS} $@"

# uncomment for linux
objs/%.o: srcs/%.c $(HDRS) | objs
	@$(CC) -c $(CFLAGS) -o $@ $(INCLUDES) $<
	@echo -e " ${PLUS} $@"

## uncomment for macOS
#$(NAME): $(OBJS)
#	@ar -rcs $(NAME) $^
#	@echo " ${PLUS} $@"
#
## uncomment for macOS
#objs/%.o: srcs/%.c $(HDRS) | objs
#	@$(CC) -c $(CFLAGS) -o $@ $(INCLUDES) $<
#	@echo " ${PLUS} $@"

objs:
	@mkdir -p $@

clean:
	@rm -fv $(OBJS) | sed -e $$'s/^/ $(MINUS) /'

fclean: clean
	@rm -fv $(NAME) | sed -e $$'s/^/ $(MINUS) /'

re: fclean all

.PHONY: all clean fclean re
