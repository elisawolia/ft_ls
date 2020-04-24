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
SRC	= main.c dir.c file.c utils.c to_del.c order.c
OBJ = $(SRC:.c=.o)

# directories

SRC_DIR = ./src
OBJ_DIR = ./obj
LIB_DIR = ./libft

# files with their paths
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ))

# compile
CC = gcc
HEADERS = -I includes
CFLAGS = -c -Wall -Werror -Wextra
LIBS = -L $(LIB_DIR) -lft

.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(HEADERS) $< -o $@

$(NAME): $(OBJS)
	@make -C $(LIB_DIR)
	@$(CC) $(OBJS) $(LIBS) -o $@
	@echo "\033[92m ------- $(NAME) built and ready ------- \033[0m"

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@make -C $(LIB_DIR) clean
	@echo "\033[92m ------- $(NAME) cleaned ------- \033[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIB_DIR) fclean
	@echo "\033[92m ------- $(NAME) fcleaned ------- \033[0m"

re: fclean all