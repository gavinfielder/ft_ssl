# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfielder <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/22 14:59:51 by gfielder          #+#    #+#              #
#    Updated: 2019/05/31 21:24:42 by gfielder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ssl
SRC=src/dispatch.c src/options_common.c src/utils_common.c \
	src/md5/md5.c src/md5/md5_command.c src/md5/md5_read.c \
	src/md5/md5_constants.c src/md5/md5_utils.c src/md5/md5_string_read.c \
	src/md5/md5_hash.c src/md5/md5_stdin_echo.c \
	src/sha256/sha256.c src/sha256/sha256_command.c \
	src/sha256/sha256_constants.c src/sha256/sha256_hash.c \
	src/sha256/sha256_utils.c src/sha256/sha256_read.c \
	src/sha256/sha256_string_read.c src/sha256/sha256_endian_fix.c \
	src/sha256/sha256_stdin_echo.c \
	src/sha224/sha224.c src/sha224/sha224_command.c \
	src/sha224/sha224_constants.c src/sha224/sha224_stdin_echo.c
SRC_MAIN=src/main.c
INC=-I inc -I lib/libft/inc
CC=clang
CFLAGS=-Wall -Wextra -Werror
LIB=-L lib/libft -lft
DEPEND=lib/libft/libft.a 

all: $(NAME)

$(NAME): $(SRC) $(SRC_MAIN) $(DEPEND)
	@$(CC) $(CFLAGS) -o $(NAME) $(INC) $(LIB) $(SRC) $(SRC_MAIN)
	@echo "$(NAME) compiled."

clean:
	@make -C lib/libft/ clean > /dev/null


fclean:
	@rm -f $(NAME)
	@make -C lib/libft/ fclean > /dev/null

re:
	@make fclean
	@make all

lib/libft/libft.a:
	@make -C lib/libft > /dev/null
