NAME = philo

SRC = philo.c \
		init.c \
		utils.c \
		actions_func.c \
		support.c \

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