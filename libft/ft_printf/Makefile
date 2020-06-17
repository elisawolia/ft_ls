NAME = libftprintf.a

CYAN_CLR = \x1b[36m
GRN_CLR  = \x1b[32m
NO_CLR	 = \x1b[00m
WRN_CLR	 = \x1b[31m
HDR_PR = NO

LIB_DIR = ../libft/
OBJ_DIR = obj/
INC_DIR = includes/

SRC_DIR = src/
SRC_FILES =	ft_printf.c\
			error.c\
			flags.c\
			flags_help.c\
			flag_x.c\
			flag_f.c\
			flag_lf.c\
			flag_o.c\
			flag_di.c\
			flag_u.c\
			flag_s.c\
			flag_c.c\
			flag_size.c\
			flag_color.c\
			flag_valid.c\
			util.c\
			buffun.c\
			offpre.c\
			calculator.c\
			float_output.c\
			float_calc.c \
			float_util.c\


HEADERS = $(INC_DIR)ft_printf.h $(LIB_DIR)$(INC_DIR)libft.h

OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

CC = gcc
CFLAGS = -Wall -Werror -Wextra
INC = -I $(INC_DIR) -I $(LIB_DIR)

all: $(NAME)

$(NAME): $(HEADERS) $(OBJ_DIR) $(OBJ)
	@$(MAKE) -C $(LIB_DIR)/
	@cp ../libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo " ---- ft_printf is ready ---- "

$(OBJ_DIR):
	@mkdir obj

#ALL_SRC_DIRS = $(SRC_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS) Makefile
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@


clean:
	@$(MAKE) -C $(LIB_DIR)/ clean
	@rm -rf $(OBJ_DIR)*
	@printf " ---- ft_printf object files have been removed! ---- \n"

fclean: clean
	@$(MAKE) -C $(LIB_DIR)/ fclean
	@rm -rf $(NAME)
	@printf " ---- $(NAME) have been removed! ---- \n"


re: fclean all

norm:
	@norminette $(SRC) $(HEADERS)

.PHONY: all clean fclean re header

