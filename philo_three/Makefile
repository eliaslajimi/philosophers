FILES =	init.c\
	main.c\
	thread.c\
	utils/ft_atoi.c\
	utils/ft_itoa.c\
	utils/ft_strdup.c\
	utils/putstr.c

SRC = $(addprefix srcs/, $(FILES))
DIR = ./srcs
CC = gcc
FLAGS = -Wall -Wextra -Werror -g
HEADR = srcs/philo_three.h
TARGET = philo_three
RM = rm
RMFLAG = -f
OBJ = $(SRC:%c=%o)

all:		$(TARGET)

$(TARGET):	$(OBJ) 
	$(CC) $(FLAGS) -o $@ $(OBJ) 
	make clean

clean:
	$(RM) $(RMFLAG) $(OBJ)

fclean: 	clean
	make clean
	$(RM) $(RMFLAG) $(TARGET)

re:		fclean all
