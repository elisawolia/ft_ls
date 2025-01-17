# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlintill <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/07 18:15:53 by rlintill          #+#    #+#              #
#    Updated: 2020/02/04 11:04:06 by rlintill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAG = -Wall -Wextra -Werror

OBJ_DIR = obj/
INC_DIR = includes/
SRC_DIR = src/

SRC_P1 = ft_memset.c\
		 ft_bzero.c\
		 ft_memcpy.c\
		 ft_memccpy.c\
		 ft_memmove.c\
		 ft_memchr.c\
		 ft_memcmp.c\
		 ft_strlen.c\
		 ft_strdup.c\
		 ft_strcpy.c\
		 ft_strncpy.c\
		 ft_strcat.c\
		 ft_strncat.c\
		 ft_strlcat.c\
		 ft_strchr.c\
		 ft_strrchr.c\
		 ft_strstr.c\
		 ft_strnstr.c\
		 ft_strcmp.c\
		 ft_strncmp.c\
		 ft_atoi.c\
		 ft_isalpha.c\
		 ft_isdigit.c\
		 ft_isalnum.c\
		 ft_isascii.c\
		 ft_isprint.c\
		 ft_toupper.c\
		 ft_tolower.c

SRC_P2 = ft_memalloc.c\
		 ft_memdel.c\
		 ft_strnew.c\
		 ft_strdel.c\
		 ft_strclr.c\
		 ft_striter.c\
		 ft_striteri.c\
		 ft_strmap.c\
		 ft_strmapi.c\
		 ft_strequ.c\
		 ft_strnequ.c\
		 ft_strsub.c\
		 ft_strjoin.c\
		 ft_strtrim.c\
		 ft_strsplit.c\
		 ft_itoa.c\
		 ft_putchar.c\
		 ft_putstr.c\
		 ft_putendl.c\
		 ft_putnbr.c\
		 ft_putchar_fd.c\
		 ft_putstr_fd.c\
		 ft_putendl_fd.c\
		 ft_putnbr_fd.c

SRC_PB = ft_lstnew.c\
		 ft_lstdelone.c\
		 ft_lstdel.c\
		 ft_lstadd.c\
		 ft_lstiter.c\
		 ft_lstmap.c

SRC_DOP = ft_swap.c\
		  ft_cwords.c\
		  ft_putw.c\
		  ft_l.c\
		  ft_itsymb.c

SRC_FILES = $(SRC_P1)\
			$(SRC_P2)\
			$(SRC_PB)\
			$(SRC_DOP)

HEADER = $(INC_DIR)libft.h

OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

all: $(NAME)

$(NAME): $(HEADERS) $(OBJ_DIR) $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf " ---- Libft is ready! ----\n"

$(OBJ_DIR):
	@mkdir obj

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@gcc $(FLAG) -I $(INC_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)*
	@printf " ---- object files have been removed! ----\n"

fclean: clean
	@rm -rf $(NAME)
	@printf " ---- $(NAME) have been removed! ----\n"

re: fclean all

.PHONY: all clean fclean re header