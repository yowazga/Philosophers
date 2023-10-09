NAME := philo_bonus

CC := cc

CFLAGS := -Wall -Werror -Wextra #-fsanitize=thread -g

SRC := main.c utils.c action_philo.c

OBJ := $(SRC:.c=.o)

all : $(NAME)


$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re