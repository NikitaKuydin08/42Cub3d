# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/27 22:09:20 by nkuydin           #+#    #+#              #
#    Updated: 2025/12/08 22:06:21 by nkuydin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I ./includes

SRCS_DIR = srcs/
OBJS_DIR = objects/

IS_DIR = ft_is/
FTIS = ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint

LST_DIR = ft_lst/
FTLST = ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone \
		ft_lstiter ft_lstlast ft_lstmap ft_lstnew ft_lstsize

MEM_DIR = ft_mem/
FTMEM = ft_bzero ft_calloc ft_memchr ft_memcmp ft_memcpy ft_memmove \
			ft_realloc

PRINTF_DIR = ft_printf/
FTPRINTF = ft_print_unsigned ft_printhex ft_printint ft_printptr \
			ft_printstr ft_printf

PUT_DIR = ft_put/
FTPUT = ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd \

STR_DIR = ft_str/
FTSTR = ft_split ft_strchr ft_strdup ft_striteri ft_strjoin \
		ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp \
		ft_strnstr ft_strrchr ft_strtrim ft_substr

TO_DIR = ft_to/
FTTO = ft_atoi ft_itoa ft_tolower ft_toupper

GNL_DIR = gnl/
GNL = get_next_line

SRCS_FILES += $(addprefix ${IS_DIR}, ${FTIS})
SRCS_FILES += $(addprefix ${LST_DIR}, ${FTLST})
SRCS_FILES += $(addprefix ${MEM_DIR}, ${FTMEM})
SRCS_FILES += $(addprefix ${PRINTF_DIR}, ${FTPRINTF})
SRCS_FILES += $(addprefix ${PUT_DIR}, ${FTPUT})
SRCS_FILES += $(addprefix ${STR_DIR}, ${FTSTR})
SRCS_FILES += $(addprefix ${TO_DIR}, ${FTTO})
SRCS_FILES += $(addprefix ${GNL_DIR}, ${GNL})

SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, ${SRCS_FILES}))
OBJS = $(addprefix ${OBJS_DIR}, $(addsuffix .o, $(SRCS_FILES)))

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
	@mkdir -p ${dir $@}
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

clean: 
	@rm -rf ${OBJS_DIR}

fclean: clean
	@rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus