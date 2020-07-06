# Makefile
LDFLAGS=-lncurses
SRC = vis.c vis_arena.c vis_attr_players.c vis_cursor.c vis_data.c
OBJ = vis.o vis_arena.o vis_attr_players.o vis_cursor.o vis_data.o
LIBFT = ../libft/libft.a
HEADERS = vis.h
all: graphic
graphic: $(LIBFT) $(OBJ)
	@gcc -Wall -Werror -Wextra $(LDFLAGS) -o $@ $^ $(LIBFT)
%.o: %.c $(HEADERS)
	@gcc -Wall -Werror -Wextra -c -o $@ $<

clean:
	@rm -rf $(OBJ)

fclean: clean	
	@rm -rf graphic

re: 
	fclean