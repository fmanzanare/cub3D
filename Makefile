define HEADER
 ________      ___  ___      ________      ________      ________
|\   ____\    |\  \|\  \    |\   __  \    |\_____  \    |\   ___ \
\ \  \___|    \ \  \\\\\  \   \ \  \|\ /_   \|____|\ /_   \ \  \_|\ \
 \ \  \        \ \  \\\\\  \   \ \   __  \        \|\  \   \ \  \ \\\ \
  \ \  \____    \ \  \\\\\  \   \ \  \|\  \      __\_\  \   \ \  \_\\\ \
   \ \_______\   \ \_______\   \ \_______\    |\_______\   \ \_______\
    \|_______|    \|_______|    \|_______|    \|_______|    \|_______|

endef
export HEADER

NAME = cub3D

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
COLOR = \033[1;32m

SRCS_RCASTER = $(addprefix ./src/, raycaster.c)
SRCS_MAP = $(addprefix ./src/map_init/, map_checker.c map_init.c map_parser.c textures_catcher.c colors_catcher.c)

OBJS_RCASTER = $(addsuffix .o, $(notdir $(basename $(SRCS_RCASTER))))
OBJS_MAP = $(addsuffix .o, $(notdir $(basename $(SRCS_MAP))))

LIBFT = ./includes/libft_plus/libft.a
LIBFT_LINK = -L./includes/libft_plus -lft
GLFW_L	= -L/sgoinfre/goinfre/Perso/$(USER)/homebrew/Cellar/glfw/3.3.7/lib/ -l glfw
MLX_I = -I./MLX42/include
MLX_L	= -L MLX42 -l mlx42

all:	mlx_lib $(NAME)

mlx_lib:
		@make -C ./MLX42

$(OBJS_RCASTER):	$(SRCS_RCASTER)
			@$(CC) $(CFLAGS) -c $(SRCS_RCASTER) $(MLX_I)

$(OBJS_MAP):	$(SRCS_MAP)
			@$(CC) $(CFLAGS) -c $(SRCS_MAP) $(MLX_I)

$(NAME):	$(OBJS_RCASTER) $(OBJS_MAP) $(LIBFT)
			@$(CC) $(CFLAGS) $(OBJS_RCASTER) $(OBJS_MAP) $(MLX_L) $(GLFW_L) $(LIBFT_LINK) $(MLX_I) -o $(NAME)
			@echo "$(COLOR)$$HEADER"

$(LIBFT):
			@make -C ./includes/libft_plus

re:			fclean all

clean:
			@rm -f $(OBJS_RCASTER) $(OBJS_MAP)
			@make -C ./includes/libft_plus clean
			@make -C ./MLX42 clean

fclean:		clean
			@rm -f $(NAME)
			@make -C ./includes/libft_plus fclean
			@make -C ./MLX42 fclean
			@echo "CLEANED"

.PHONY: all clean fclean re header mlx_lib
