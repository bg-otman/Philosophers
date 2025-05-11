CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread
SRC = main.c philo.c helpers_funs.c init.c
OBJ = $(SRC:.c=.o)
NAME = philo

all: $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : clean
