# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mmarcell <mmarcell@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/02/14 13:21:34 by mmarcell      #+#    #+#                  #
#    Updated: 2020/04/27 13:07:43 by mmarcell      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include srcs/_file_names

NAME := libft.a

OBJS := $(FILES:%.c=objs/%.o)

CFLAGS := -Wall -Wextra -Werror

HDRS_PATH := .
INCLUDES := -I $(HDRS_PATH)
HDRS := $(HDRS_PATH)/libft.h

PLUS := $$(tput setaf 2)+$$(tput sgr0)
MINUS := $$(tput setaf 1)-$$(tput sgr0)

all: $(NAME)

$(NAME): $(OBJS)
	@ar -rcs $(NAME) $^
	@echo " ${PLUS} $@"

objs/%.o: srcs/%.c $(HDRS) | objs
	@$(CC) -c $(CFLAGS) -o $@ $(INCLUDES) $<
	@echo " ${PLUS} $@"

objs:
	@mkdir -p $@

clean:
	@rm -fv $(OBJS) | sed "s/^/ $(MINUS) /"

fclean: clean
	@rm -fv $(NAME) | sed "s/^/ $(MINUS) /"

re: 
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean objs re
