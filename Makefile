


NAME = cub3D

CC = cc
MLXFL = libmlx42.a -Iinclude -lglfw
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = ./MLX42
LIBFT_DIR = ./libft
OBJ_DIR = ./objects/
SRCS_DIR = ./srcs/

BREW_PREFIX = $(shell brew --prefix)
HEADERS = -I ${MLX_DIR}/include -I ${LIBFT_DIR} -I ${BREW_PREFIX}/include
LIBS = ${MLX_DIR}/build/libmlx42.a ${LIBFT_DIR}/libft.a -L ${BREW_PREFIX}/lib -ldl -lglfw -pthread -lm
SRC = main.c \
	init.c \
	validation/permission.c \
	validation/validate.c \
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
$(OBJ_DIR)%.o: srcs/%.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} ${HEADERS} -c $< -o $@

# Build libft
libft:
	@make -C ${LIBFT_DIR}

# Build MLX42
mlx:
	@cmake -S ${MLX_DIR} -B ${MLX_DIR}/build
	@cmake --build ${MLX_DIR}/build -j4

bonus:


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