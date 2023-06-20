#include "../../includes/cub3D.h"

static void	ft_put_image(t_rc *data)
{
	int	x_map;
	int	y_map;

	x_map = (MAP_WIDTH / 2) - (P_SIZE / 2);
	y_map = (MAP_HEIGHT / 2) - (P_SIZE / 2);
	mlx_image_to_window(data->mlx, data->img_map, 0, 0);
	mlx_image_to_window(data->mlx, data->img_p, x_map, y_map);
	mlx_image_to_window(data->mlx, data->img_h, 0, 0);
}

void	is_wall_conditions(t_rc *data, int xp, int yp, char type)
{
	if (data->map->map[(int)data->player.y
			/ (MAP_HEIGHT / data->map->height)][xp] == '0' && type == 'W')
		data->player.x += data->player.dx;
	if (data->map->map[yp][(int)data->player.x
		/ (MAP_WIDTH / data->map->width)] == '0' && type == 'W')
		data->player.y += data->player.dy;
	if (data->map->map[(int)data->player.y
			/ (MAP_HEIGHT / data->map->height)][xp] == '0' && type == 'S')
		data->player.x -= data->player.dx;
	if (data->map->map[yp][(int)data->player.x
		/ (MAP_WIDTH / data->map->width)] == '0' && type == 'S')
		data->player.y -= data->player.dy;
	if (data->map->map[(int)data->player.y
			/ (MAP_HEIGHT / data->map->height)][xp] == '0' && type == 'A')
		data->player.x += data->player.dy;
	if (data->map->map[yp][(int)data->player.x
		/ (MAP_WIDTH / data->map->width)] == '0' && type == 'A')
		data->player.y -= data->player.dx;
	if (data->map->map[(int)data->player.y
			/ (MAP_HEIGHT / data->map->height)][xp] == '0' && type == 'D')
		data->player.x -= data->player.dy;
	if (data->map->map[yp][(int)data->player.x
		/ (MAP_WIDTH / data->map->width)] == '0' && type == 'D')
		data->player.y += data->player.dx;
}

void	ft_is_wall(t_rc *data, double py, double px, char type)
{
	int		yp;
	int		xp;

	yp = (int)py / (MAP_HEIGHT / data->map->height);
	xp = (int)px / (MAP_WIDTH / data->map->width);
	is_wall_conditions(data, xp, yp, type);
	data->img_p->instances[0].y = data->player.y;
	data->img_p->instances[0].x = data->player.x;
}

void	ft_print_player(t_rc *data)
{
	int	*pointer;
	int	p;

	p = 0;
	pointer = (int *)data->img_p->pixels;
	while ((unsigned int)p < data->img_p->width * data->img_p->height)
		pointer[p++] = 0xFF00FFFF;
}

int32_t	main(int argc, char **argv)
{
	t_rc		data;
	t_init		init;

	arg_checker(argc, argv, &init);
	data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	if (!data.mlx)
		return (EXIT_FAILURE);
	ft_init(&data, &init);
	world_builder(&data);
	data.texs[0] = mlx_load_png(data.map->n_tex);
	data.texs[1] = mlx_load_png(data.map->s_tex);
	data.texs[2] = mlx_load_png(data.map->w_tex);
	data.texs[3] = mlx_load_png(data.map->e_tex);
	raycast(&data);
	mlx_image_to_window(data.mlx, data.img_bg, 0, 0);
	mlx_image_to_window(data.mlx, data.img_world, 0, 0);
	ft_put_image(&data);
	mlx_key_hook(data.mlx, &ft_key_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
