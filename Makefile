CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
HEADERS= ./includes/philo.h
MAIN = ./src/main.o
SOURCES = ./src/utils/ft_split.o ./src/utils/ft_putstr_fd.o ./src/utils/ft_atoi.o ./src/utils/add_back.o ./src/utils/clear.o\
./src/utils/new.o ./src/utils/size.o ./src/utils/last.o
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