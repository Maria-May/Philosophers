NAME = philo_bonus

SRC = philo_bonus.c \
		init_bonus.c \
		utils_bonus.c \
		actions_func_bonus.c \

INCLUDES = philo.h  

OBJ = $(patsubst %.c, %.o, $(SRC))

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
		cc $(FLAGS) $(OBJ) -o $(NAME)

%.o : %.c	$(INCLUDES) 
		cc $(FLAGS) -c $< -o $@

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all 

.PHONY: all clean fclean re 
