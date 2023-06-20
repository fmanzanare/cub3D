define HEADER
                              Project
                                by
                    ObiWanFernando & cooperMaker
 ________      ___  ___      ________      ________      ________
|\   ____\    |\  \|\  \    |\   __  \    |\_____  \    |\   ___ \\
\ \  \___|    \ \  \\\\\  \   \ \  \|\ /_   \|____|\ /_   \ \  \_|\ \\
 \ \  \        \ \  \\\\\  \   \ \   __  \        \|\  \   \ \  \ \\\ \\
  \ \  \____    \ \  \\\\\  \   \ \  \|\  \      __\_\  \   \ \  \_\\\ \\
   \ \_______\   \ \_______\   \ \_______\    |\_______\   \ \_______\\
    \|_______|    \|_______|    \|_______|    \|_______|    \|_______|

endef
export HEADER
NAME = cub3D

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
COLOR = \033[1;32m

SRCS_MAP = $(addprefix ./src/parser/, inputs_checker.c map_init.c map_parser.c textures_catcher.c colors_catcher.c map_catcher.c map_normalizer.c map_checker.c color_converter.c)
SRCS_RCASTER = $(addprefix ./src/raycasting/, raycaster.c)
SRCS_WORLD_BUILDER = $(addprefix ./src/world_builder/, world_builder.c raycast.c textures.c)
SRCS_CUB3D_UTILS = $(addprefix ./src/cub3d_utils/, free_fts.c ft_errexit.c)

OBJS_RCASTER = $(addsuffix .o, $(notdir $(basename $(SRCS_RCASTER))))
OBJS_MAP = $(addsuffix .o, $(notdir $(basename $(SRCS_MAP))))
OBJS_WORLD_BUILDER = $(addsuffix .o, $(notdir $(basename $(SRCS_WORLD_BUILDER))))
OBJS_CUB3D_UTILS = $(addsuffix .o, $(notdir $(basename $(SRCS_CUB3D_UTILS))))

LIBFT = ./includes/libft_plus/libft.a
LIBFT_LINK = -L./includes/libft_plus -lft
GLFW_L	= -L/sgoinfre/goinfre/Perso/$(USER)/homebrew/Cellar/glfw/3.3.7/lib/ -l glfw
MLX = ./MLX42/libmlx42.a
MLX_I = -I./MLX42/include
MLX_L	= -L MLX42 -l mlx42

all:	$(NAME)

$(OBJS_RCASTER):	$(SRCS_RCASTER)
			@$(CC) $(CFLAGS) -c $(SRCS_RCASTER) $(MLX_I)

$(OBJS_MAP):	$(SRCS_MAP)
			@$(CC) $(CFLAGS) -c $(SRCS_MAP) $(MLX_I)

$(OBJS_WORLD_BUILDER):	$(SRCS_WORLD_BUILDER)
			@$(CC) $(CFLAGS) -c $(SRCS_WORLD_BUILDER) $(MLX_I)

$(OBJS_CUB3D_UTILS):	$(SRCS_CUB3D_UTILS)
			@$(CC) $(CFLAGS) -c $(SRCS_CUB3D_UTILS) $(MLX_I)

$(NAME):	$(OBJS_RCASTER) $(OBJS_MAP) $(OBJS_WORLD_BUILDER) $(OBJS_CUB3D_UTILS) $(LIBFT) $(MLX)
			@$(CC) $(CFLAGS) $(OBJS_RCASTER) $(OBJS_MAP) $(OBJS_WORLD_BUILDER) $(OBJS_CUB3D_UTILS) $(MLX_L) $(GLFW_L) $(LIBFT_LINK) -o $(NAME)
			@echo "$(COLOR)$$HEADER"

$(LIBFT):
			@make -C ./includes/libft_plus

$(MLX):
			@make -C ./MLX42

re:			fclean all

clean:
			@rm -f $(OBJS_RCASTER) $(OBJS_MAP) $(OBJS_WORLD_BUILDER) $(OBJS_CUB3D_UTILS)
			@make -C ./includes/libft_plus clean
			@make -C ./MLX42 clean

fclean:		clean
			@rm -f $(NAME)
			@make -C ./includes/libft_plus fclean
			@make -C ./MLX42 fclean
			@echo "CLEANED"

.PHONY: all, clean, fclean, re, header
