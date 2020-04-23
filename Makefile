# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mmarcell <mmarcell@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/07 18:47:20 by mmarcell      #+#    #+#                  #
#    Updated: 2020/04/23 12:59:06 by moana         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include srcs/_files

NAME := corewar

OBJS := $(FILES:%.c=objs/%.o) objs/main.o

CFLAGS := -Wall -Wextra -Werror -g

LIBFT_PATH := libft
LIBFT := $(LIBFT_PATH)/libft.a

INCLUDES_PATH := includes
INCLUDES := -I $(INCLUDES_PATH) -I $(LIBFT_PATH)
HDRS := $(INCLUDES_PATH)/corewar.h

PLUS := \033[0;32m+\033[0;00m
MINUS := \033[0;31m-\033[0;00m

all: $(NAME)

# uncomment for linux
$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)
	@echo -e " $(PLUS) $@"

# uncomment for linux
objs/%.o: srcs/%.c $(HDRS) | objs
	@$(CC) -c $(CFLAGS) -o $@ $(INCLUDES) $<
	@echo -e " $(PLUS) $@"

## uncomment for macOS
#$(NAME): $(LIBFT) $(OBJS)
#	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)
#	@echo " $(PLUS) $@"
#
## uncomment for macOS
#objs/%.o: srcs/%.c $(HDRS) | objs
#	@$(CC) -c $(CFLAGS) -o $@ $(INCLUDES) $<
#	@echo " $(PLUS) $@"

objs:
	@mkdir -p $@

$(LIBFT): FORCE
	@make -C $(LIBFT_PATH) | sed -e $$'s/^/$(LIBFT_PATH): /'

clean: lclean
	@make clean -C $(LIBFT_PATH) | sed -e $$'s/^/$(LIBFT_PATH): /'

lclean:
	@rm -rfv objs | sed -e $$'s/^/ $(MINUS) /'

fclean: clean lfclean
	@rm -fv $(LIBFT) | sed -e $$'s/^/ $(MINUS) /'

lfclean: lclean
	@rm -fv $(NAME) | sed -e $$'s/^/ $(MINUS) /'

re: fclean all

lre: lfclean all

test: $(LIBFT) $(OBJS) $(HDRS)
	@make -C tests

FORCE:

.PHONY: all clean fclean re FORCE
