NAME := philo

CC := cc

#-fsanitize=thread -g
CFLAGS := -Wall -Werror -Wextra 

SRC := main.c action_philo.c check_threads.c utils.c

OBJ := $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re