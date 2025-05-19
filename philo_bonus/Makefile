CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
SRC = main_bonus.c philo_bonus.c helpers_bonus.c init_bonus.c utils_bonus.c
OBJ = $(SRC:.c=.o)
NAME = philo_bonus

all: $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo_bonus.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : clean
