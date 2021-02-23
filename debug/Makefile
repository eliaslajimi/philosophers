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
FLAGS = -Wall -Wextra -Werror
HEADR = srcs/philo_one.h
TARGET = philo_one 
RM = rm
RMFLAG = -f
OBJ = $(SRC:%c=%o)

all:		$(TARGET)

$(TARGET):	$(OBJ) 
	$(CC) $(FLAGS) -o $@ $(OBJ) $(HEADR)
	make clean

clean:
	$(RM) $(RMFLAG) $(OBJ)

fclean: 	clean
	make clean
	$(RM) $(RMFLAG) $(TARGET)

re:		fclean all

#mac:		$(OBJ)
#	@gcc -o $(TARGET) $(FLAGS) $(OBJ)
#	@make clean
#	@echo "Compilation\t\t\033[0;32m[OK]\033[0m"

