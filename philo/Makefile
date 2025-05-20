CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c philo.c helpers_funs.c init.c utils.c
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
