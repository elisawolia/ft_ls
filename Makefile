# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlintill <rlintill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/24 17:10:27 by rlintill          #+#    #+#              #
#    Updated: 2020/04/24 17:23:29 by rlintill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

# files
SRC	= main.c dir.c file.c utils.c to_del.c order.c print.c
OBJ = $(SRC:.c=.o)

LIBFT_A = libft.a
FT_PRINTF_A = libftprintf.a

# directories

SRC_DIR = ./src
OBJ_DIR = ./obj
EXTRA_DIR = ./libft
LIB_DIR = $(EXTRA_DIR)/libft/
PRINTF_DIR = $(EXTRA_DIR)/ft_printf/

# files with their paths
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ))

# compile
CC = gcc
HEADERS = -I includes
LIB_HEADERS =  -I $(LIB_DIR)includes -I $(PRINTF_DIR)includes
CFLAGS = -c -Wall -Werror -Wextra
LIB = -L . $(LIBFT_A) -lft -L . $(FT_PRINTF_A) -lft

.PHONY: all clean fclean re

all: do_lib $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIB) -o $@
	@echo "\033[92m ------- $(NAME) built and ready ------- \033[0m"

do_lib:
	@make -C $(PRINTF_DIR)
	@cp $(LIB_DIR)$(LIBFT_A) .
	@cp $(PRINTF_DIR)$(FT_PRINTF_A) .

clean:
	@/bin/rm -rf $(OBJ_DIR) $(LIBFT_A) $(FT_PRINTF_A)
	@make -C $(PRINTF_DIR) clean
	@echo "\033[92m ------- $(NAME) cleaned ------- \033[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(PRINTF_DIR) fclean
	@echo "\033[92m ------- $(NAME) fcleaned ------- \033[0m"

re: fclean all