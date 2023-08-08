CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
HEADERS= ./includes/philo.h
MAIN = ./src/main.o
SOURCES = ./src/utils/parsing.o\
	./src/utils/ft_atoi.o\
	./src/utils/ft_putstr_fd.o\
	./src/utils/utils.o\
	./src/utils/utils2.o\
	./src/utils/freeing.o\


all : $(NAME)

$(NAME) : $(SOURCES) $(MAIN)
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN) $(SOURCES)

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -I./includes -c $< -o $@

clean :
	rm -f $(SOURCES) $(MAIN)

fclean :
	rm -f $(SOURCES) $(MAIN) $(NAME)

re : fclean all

.PHONY: fclean clean re all