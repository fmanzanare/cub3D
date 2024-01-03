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
CFLAGS = -Wall -Werror -Wextra -g3
COLOR = \033[1;32m

VPATH	= ./src/parser/:./src/cub3d_utils/:./src/raycasting/:./src/world_builder/

SRCS_MAP = inputs_checker.c map_init.c map_parser.c textures_catcher.c colors_catcher.c map_catcher.c map_normalizer.c map_checker.c color_converter.c
SRCS_WORLD_BUILDER = world_builder.c raycast.c textures.c
SRCS_CUB3D_UTILS = free_fts.c ft_errexit.c ft_atoi_checker.c
SRCS_RCASTER = main.c minimap.c init.c hooks.c collisions.c motion.c rotation.c

OBJS_RCASTER = $(SRCS_RCASTER:.c=.o)
OBJS_MAP = $(SRCS_MAP:.c=.o)
OBJS_WORLD_BUILDER = $(SRCS_WORLD_BUILDER:.c=.o)
OBJS_CUB3D_UTILS = $(SRCS_CUB3D_UTILS:.c=.o)

LIBFT = ./includes/libft_plus/libft.a
LIBFT_LINK = -L./includes/libft_plus -lft
GLFW_L	= -L/sgoinfre/goinfre/Perso/$(USER)/homebrew/Cellar/glfw/3.3.9/lib/ -l glfw
MLX = ./MLX42/libmlx42.a
MLX_I = -I./MLX42/include
MLX_L	= -L MLX42 -l mlx42

all:	$(NAME)

$(NAME):	$(OBJS_RCASTER) $(OBJS_MAP) $(OBJS_WORLD_BUILDER) $(OBJS_CUB3D_UTILS) $(LIBFT) $(MLX)
			@$(CC) $(CFLAGS) $(OBJS_RCASTER) $(OBJS_MAP) $(OBJS_WORLD_BUILDER) $(OBJS_CUB3D_UTILS) $(MLX_L) $(GLFW_L) $(LIBFT_LINK) -o $(NAME)
			@echo "$(COLOR)$$HEADER"

$(LIBFT):
			@make -C ./includes/libft_plus

$(MLX):
			@make -C ./MLX42

%.o:	%.c
			@$(CC) $(CFLAGS) -c $<

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
