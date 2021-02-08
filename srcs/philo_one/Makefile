#elajimi - 07/02/2020

CC=gcc
FLAGS=-Wall -Wextra -Werror -I srcs/.
SRCDIR=./srcs
UTILDIR=./utils
TARGET=philo_one

SRCS= srcs/main.c \
      utils/ft_atoi.c
OBJ = $(SRCS:%c=%o)

philo_one: $(OBJ)
	$(CC) $(FLAGS) $^ -o $@ 
	$(clean)
clean:
	rm -f $(OBJ)
#$(SRCDIR)/%.o:%.c 
#	$(CC) $(FLAGS) -c $< -o $@ 

