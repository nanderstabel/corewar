# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mmarcell <mmarcell@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/07 18:47:20 by mmarcell      #+#    #+#                  #
#    Updated: 2020/05/07 13:54:44 by nstabel       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include srcs/_files.mk

COR_NAME := corewar

ASM_NAME := asm

COR_OBJS := $(COR_FILES:%.c=objs/%.o) objs/cor_main.o

ASM_OBJS := $(ASM_FILES:%.c=objs/%.o) objs/asm_main.o

CFLAGS := -Wall -Wextra -Werror -g
LDFLAGS = -lncurses

LIBFT_PATH := libft
LIBFT := $(LIBFT_PATH)/libft.a

INCLUDES_PATH := includes
INCLUDES := -I $(INCLUDES_PATH) -I $(LIBFT_PATH)
HDRS := $(INCLUDES_PATH)/corewar.h $(INCLUDES_PATH)/asm.h $(INCLUDES_PATH)/op.h \
	$(INCLUDES_PATH)/vis.h $(INCLUDES_PATH)/cor_errors.h

PLUS := $$(tput setaf 2)+$$(tput sgr0)
MINUS := $$(tput setaf 1)-$$(tput sgr0)

MAX_PARALLEL = 6

all: $(COR_NAME) $(ASM_NAME)

$(COR_NAME): $(LIBFT) $(COR_OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT) $(LDFLAGS)
	@echo " $(PLUS) $@"

$(ASM_NAME): $(LIBFT) $(ASM_OBJS)
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
	@+make -C $(LIBFT_PATH) | sed "s/^/libft: /"

clean: lclean
	@+make clean -C $(LIBFT_PATH) | sed "s/^/libft: /"

lclean:
	@rm -rfv objs | sed "s/^/ $(MINUS) /"

fclean: clean lfclean
	@rm -fv $(LIBFT) | sed "s/^/ $(MINUS) /"

lfclean: lclean
	@rm -fv $(COR_NAME) $(ASM_NAME) | sed "s/^/ $(MINUS) /"

re:
	$(MAKE) fclean
	$(MAKE) all

lre:
	$(MAKE) lfclean
	$(MAKE) all

test: $(LIBFT) $(OBJS) $(HDRS)
	@$(MAKE) all
	@make re -C test_folder/criterion
	@echo "\n		---- ASM ----		\n"
	@./test_folder/criterion/asm_test
	@echo "\n		---- VM ----		\n"
	@./test_folder/criterion/cor_test

FORCE:

.PHONY: all clean fclean lclean lfclean lre test re multi objs FORCE
