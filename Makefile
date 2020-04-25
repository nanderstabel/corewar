# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mmarcell <mmarcell@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/07 18:47:20 by mmarcell      #+#    #+#                  #
#    Updated: 2020/04/25 21:23:01 by mmarcell      ########   odam.nl          #
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

PLUS := $$(tput setaf 2)+$$(tput sgr0)
MINUS := $$(tput setaf 1)-$$(tput sgr0)

MAX_PARALLEL = 6

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)
	@echo " $(PLUS) $@"

objs/%.o: srcs/%.c $(HDRS) | objs
	@$(CC) -c $(CFLAGS) -o $@ $(INCLUDES) $<
	@echo " $(PLUS) $@"

objs:
	@mkdir -p $@

multi:
	@$(MAKE) -j$(MAX_PARALLEL) all

$(LIBFT): FORCE
	@+make -C $(LIBFT_PATH) | sed -e $$'s/^/$(LIBFT_PATH): /'

clean: lclean
	@+make clean -C $(LIBFT_PATH) | sed -e $$'s/^/$(LIBFT_PATH): /'

lclean:
	@rm -rfv objs | sed "s/removed / $(MINUS) /"

fclean: clean lfclean
	@rm -fv $(LIBFT) | sed "s/removed / $(MINUS) /"

lfclean: lclean
	@rm -fv $(NAME) | sed "s/removed / $(MINUS) /"

re:
	$(MAKE) fclean
	$(MAKE) all

lre:
	$(MAKE) lfclean
	$(MAKE) all

test: $(LIBFT) $(OBJS) $(HDRS)
	@make -C tests

FORCE:

.PHONY: all clean fclean lclean lfclean lre test re multi objs FORCE
