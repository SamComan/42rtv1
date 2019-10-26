.PHONY: fclean clean all re

NAME = rtv1

SRC_NAME = main.c parsing.c lists.c

SRC_PATH = src/
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))

FLAGS = -Wall -Wextra -Werror -Ofast

HEADERS = ./header
HEAD = header/rtv1.h

MLX_PATH = includes/minilibx_macos/
MLX = $(addprefix $(MLX_PATH), libmlx.a)

LIBFT_PATH = includes/libft/
LIBFT = $(addprefix $(LIBFT_PATH), libft.a)

FRAMEWORKS = -framework OpenGl -framework Appkit

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_PATH = obj/
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: $(MLX) $(LIBFT) $(NAME)

$(MLX):
	@make -C $(MLX_PATH)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(HEAD) $(OBJ)
	@gcc $(FLAGS) -o $@ $(OBJ) -L $(MLX_PATH) -lmlx -L $(LIBFT_PATH) -lft $(FRAMEWORKS)
	@echo "\n\033[1;32m---------->[RTV1 IS READY]<----------- \033[0m\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEAD)
	@mkdir -p obj
	gcc $(FLAGS) -o $@ -c $< -I $(HEADERS)

clean:
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(MLX_PATH)
	@rm -rf $(OBJ_PATH)
	@echo "\n\033[1;31m---------->[.O REMOVED]<----------- \033[0m"

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)
	@echo "\n\033[1;31m----------->[RTV1 REMOVED]<-------- \033[0m"

re: fclean all