NAME = miniRT

CC = gcc
CFLAGS = -Wall -Wextra -Werror 
# -g3 -fsanitize=address
RM = rm -f

SRC = ./src/main.c ./src/check.c ./src/load.c ./src/utils/utils.c \
		./src/amb.c ./src/cameras/camera.c ./src/lum.c ./src/spher.c ./src/cyl.c \
		./src/plan.c ./src/cameras/camera2.c ./src/image/image.c \
		./src/intersections/intersections.c \
		./src/rays/ray.c ./src/exit.c ./src/utils/utils2.c \
		./src/shapes/shapes.c ./src/vectors/vector.c ./src/color.c \
		./src/vectors/vector2.c ./src/vectors/vector3.c ./src/error.c\
		./src/vectors/vector_operations.c ./src/hit.c ./src/utils/split_words.c \
		./src/utils/ft_split.c

OBJ = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	${CC} $(CFLAGS) ${OBJ} -lGL -lGLU -lglut -Iinclude -ldl -lbsd -pthread -lm -o ${NAME}

%.o: %.c
	$(CC) $(CFLAGS) -I./inc  -c $< -o $@

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: clean fclean re all
