NAME = miniRT

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
RM = rm -f

SRC = ./src/main.c ./src/check.c ./src/load.c ./src/utils.c ./src/error.c \
		./src/amb.c ./src/cameras/camera.c ./src/lum.c ./src/spher.c ./src/cyl.c \
		./src/plan.c ./src/cameras/camera2.c ./src/image/image.c \
		./src/intersections/intersections.c ./src/intersections/intersections2.c \
		./src/rays/ray.c ./src/hooks.c ./src/exit.c ./src/utils2.c \
		./src/shapes/shapes.c ./src/vectors/vector.c ./src/color.c \
		./src/vectors/vector2.c ./src/vectors/vector3.c \
		./src/vectors/vector_operations.c ./src/hit.c ./src/ft_split_words.c

OBJ = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	${MAKE} -sC ./libft
	mv ./libft/libft.a ./
	${CC} $(CFLAGS) ${OBJ} libft.a -lglfw -lGL -Iinclude -ldl -pthread -L/Users/${USER}/.brew/opt/glfw/lib/ -lm -o ${NAME}

%.o: %.c
	$(CC) $(CFLAGS)  -I./inc -I/Users/${USER}/.brew/opt/glfw/include -I/Users/${USER}/goinfre/.brew/opt/glfw/include -c $< -o $@

clean:
	${RM} ${OBJ} libft.a
	${MAKE} clean -sC ./libft

fclean: clean
	${RM} ${NAME}
	${MAKE} fclean -sC ./libft

re: fclean all

.PHONY: clean fclean re all
