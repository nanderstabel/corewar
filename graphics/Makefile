# Makefile
LDFLAGS=-lncurses
SRC = vis_arena.c vis_attr_players.c corewargraphicdemo.c
OBJ = vis_arena.o vis_attr_players.o corewargraphicdemo.o
LIBFT = ../libft/libft.a
HEADERS = vis.h
all: graphic
graphic: $(LIBFT) $(OBJ)
	gcc -Wall -Werror -Wextra $(LDFLAGS) -o $@ $^ $(LIBFT)
%.o: %.c $(HEADERS)
	gcc -Wall -Werror -Wextra -c -o $@ $<

fclean:
	rm -rf $(OBJ)
	rm -rf corewargraphicdemo.o
	rm -rf vis_attr_players.o
	rm -rf vis_arena.o
	rm -rf graphic

re:
	make fclean
	make all