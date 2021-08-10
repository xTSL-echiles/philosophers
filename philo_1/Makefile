NAME =  philo
INCLUDE = philo.h
SRC =		main.c\
			mutex.c \
			structs_setup.c \
			utils.c  

OBJ_NAME	= $(SRC:.c=.o)
CC			= gcc -g -O2 -Wall -Wextra -Werror
RM	= rm -f
$(NAME):	$(OBJ_NAME) philo.h
			$(CC) -o $(NAME) $(OBJ_NAME)
all:		$(NAME)
clean:
			$(RM) $(OBJ_NAME)
fclean:		clean
			$(RM) ${NAME}
re:			fclean all