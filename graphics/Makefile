# Makefile
LDFLAGS=-lncurses
SRC = ft_attr_players.c corewargraphicdemo.c
OBJ = ft_attr_players.o corewargraphicdemo.o
LIBFT = ../libft/libft.a
HEADERS = graphics.h
all: graphic
graphic: $(LIBFT) $(OBJ)
	gcc -Wall -Werror -Wextra $(LDFLAGS) -o $@ $^ $(LIBFT)
%.o: %.c $(HEADERS)
	gcc -Wall -Werror -Wextra -c -o $@ $<

fclean:
	rm -rf $(OBJ)
	rm -rf corewargraphicdemo.o
	rm -rf ft_attr_players.o
	rm -rf graphic

re:
	make fclean
	make all