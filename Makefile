CC = cc
CFLAGS =
NAME = philo
HEADERS= ./includes/philo.h
SOURCES = ./src/main.o ./src/utils/ft_split.o ./src/utils/ft_putstr_fd.o \
 ./src/utils/ft_atoi.o ./src/utils/add_back.o ./src/utils/clear.o \
./src/utils/new.o ./src/utils/size.o ./src/utils/last.o ./src/utils/utils.o

all : $(NAME)

$(NAME) : $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(NAME)

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -I./includes -c $< -o $@

clean :
	rm -f $(SOURCES)

fclean :
	rm -f $(SOURCES) $(NAME)

re : fclean all

.PHONY: fclean clean re all