
NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = ./MLX42
LIBFT_DIR = ./libft
OBJ_DIR = objects/
SRCS_DIR = srcs/

HEADERS = -I ${MLX_DIR}/include -I ${LIBFT_DIR}
LIBS = ${MLX_DIR}/build/libmlx42.a ${LIBFT_DIR}/libft.a -pthread -lm -lglfw
SRC = main.c \
	init.c \
	parsing/permission.c \
	parsing/validate.c \
	utils/error.c

SRCS = ${addprefix $(SRCS_DIR), $(SRC)}

OBJ = $(SRC:.c=.o)
OBJS = ${addprefix ${OBJ_DIR}, ${OBJ}}

all: mlx libft ${NAME} ${OBJ_DIR}

# Ensure object directory exists
${OBJ_DIR}:
	mkdir -p ${OBJ_DIR}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LIBS} -o $@

# Compile object files
$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} ${HEADERS} -c $< -o $@

# Build libft
libft:
	@make -C ${LIBFT_DIR}

# Build MLX42
mlx:
	@cmake -S ${MLX_DIR} -B ${MLX_DIR}/build
	@cmake --build ${MLX_DIR}/build -j4

# Clean objects
clean:
	rm -rf ${OBJ_DIR}
	@make -C ${LIBFT_DIR} clean

# Clean everything
fclean: clean
	rm -f ${NAME}
	rm -rf ${MLX_DIR}/build
	@make -C ${LIBFT_DIR} fclean

# Rebuild
re: fclean all

.PHONY: all clean fclean re mlx libft