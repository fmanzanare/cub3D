#include "../../includes/cub3D.h"

// int	map[][8] =
// {
// 	{1,1,1,1,1,1,1,1,},
// 	{1,0,1,0,0,0,0,1,},
// 	{1,0,1,0,0,0,0,1,},
// 	{1,0,1,0,0,0,0,1,},
// 	{1,0,0,0,0,0,0,1,},
// 	{1,0,0,0,0,1,0,1,},
// 	{1,0,0,0,0,0,0,1,},
// 	{1,1,1,1,1,1,1,1,},
// };

void	ft_rotation(mlx_key_data_t keydata, t_rc *data)
{
	if (keydata.key == MLX_KEY_LEFT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		data->player.alpha -= ALPHA_INC;
		if (data->player.alpha < 0)
			data->player.alpha += 2 * PI;
		data->player.dx = cos(data->player.alpha) * MULT_DELTA;
		data->player.dy = sin(data->player.alpha) * MULT_DELTA;
	}
	if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		data->player.alpha += ALPHA_INC;
		if (data->player.alpha > 2 * PI)
			data->player.alpha -= 2 * PI;
		data->player.dx = cos(data->player.alpha) * MULT_DELTA;
		data->player.dy = sin(data->player.alpha) * MULT_DELTA;
	}
}

int	is_wall(t_rc *data, double py, double px)
{
	int	x;
	int	y;

	x = (int)px /(MAP_WIDTH / data->map->width);
	y = (int)py /(MAP_HEIGHT / data->map->height);
	return data->map->map[y][x] == '1';
}

void	ft_is_wall(t_rc *data, double py, double px, char type)
{
	int	yp;
	int	xp;
	char **map = data->map->map;

	yp = (int)py / (MAP_HEIGHT / data->map->height);
	xp = (int)px / (MAP_WIDTH / data->map->width);
	if (map[(int)data->player.y / (MAP_HEIGHT / data->map->height)][xp] == '0' && type == 'W')
		data->player.x += data->player.dx;
	if (map[yp][(int)data->player.x / (MAP_WIDTH / data->map->width)] == '0' && type == 'W')
		data->player.y += data->player.dy;
	if (map[(int)data->player.y / (MAP_HEIGHT / data->map->height)][xp] == '0' && type == 'S')
		data->player.x -= data->player.dx;
	if (map[yp][(int)data->player.x / (MAP_WIDTH / data->map->width)] == '0' && type == 'S')
		data->player.y -= data->player.dy;
	if (map[(int)data->player.y / (MAP_HEIGHT / data->map->height)][xp] == '0' && type == 'A')
		data->player.x += data->player.dy;
	if (map[yp][(int)data->player.x / (MAP_WIDTH / data->map->width)] == '0' && type == 'A')
		data->player.y -= data->player.dx;
	if (map[(int)data->player.y / (MAP_HEIGHT / data->map->height)][xp] == '0' && type == 'D')
		data->player.x -= data->player.dy;
	if (map[yp][(int)data->player.x / (MAP_WIDTH / data->map->width)] == '0' && type == 'D')
		data->player.y += data->player.dx;
	data->img_p->instances[0].y = data->player.y;
	data->img_p->instances[0].x = data->player.x;
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_rc	*data;
	int		t;

	t = -1;
	data = (t_rc *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
	{
		mlx_terminate(data->mlx);
		exit(0);
	}
	if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		ft_is_wall(data, data->player.y + data->player.dy,data->player.x + data->player.dx, 'W');
	if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		ft_is_wall(data, data->player.y - data->player.dy,data->player.x - data->player.dx, 'S');
	if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		ft_is_wall(data, data->player.y - data->player.dx, data->player.x + data->player.dy, 'A');
	if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		ft_is_wall(data, data->player.y + data->player.dx, data->player.x - data->player.dy, 'D');
	ft_rotation(keydata, data);
	raycast(data);
	// cabeza del jugador
	memset(data->img_h->pixels, 0,data->img_h->width * data->img_h->height * 4 );
	while (t++ < MAP_WIDTH && !is_wall(data, data->player.y + 2 + t * (data->player.dy/MULT_DELTA), data->player.x + 2 + t * (data->player.dx/MULT_DELTA)))
		mlx_put_pixel(data->img_h, data->player.x + 2 + t * (data->player.dx/MULT_DELTA), (data->player.y + 2) + t * (data->player.dy/MULT_DELTA), 0xFF00FFFF);
}

void	ft_print_player(t_rc *data)
{
	int	*pointer;
	int	p;
	p = 0; // iterador
	pointer = (int *)data->img_p->pixels;
	while ((unsigned int)p < data->img_p->width * data->img_p->height)
		pointer[p++] = 0xFF00FFFF;
}

void	ft_init(t_rc *data, t_init *init)
{
	data->map = init->map;
	// data->map->width = 8;
	// data->map->height = 8;
	// init de player
	data->img_p = mlx_new_image(data->mlx, P_SIZE, P_SIZE);
	memset(data->img_p->pixels, 255, data->img_p->width * data->img_p->height * 4);
	data->img_h = mlx_new_image(data->mlx, MAP_WIDTH, MAP_HEIGHT);
	data->player.alpha = 0;
	data->player.x = 120;
	data->player.y = 150;
	data->player.dx = cos(data->player.alpha) * 5;
	data->player.dy = sin(data->player.alpha) * 5;
	ft_print_player(data);
	// init de map
	data->img_map = mlx_new_image(data->mlx, MAP_WIDTH, MAP_HEIGHT);
	memset(data->img_map->pixels, 255, data->img_map->width * data->img_map->height * 4);
}

void	ft_print_minimap(t_rc *data)
{
	int	y;
	int	x;
	int	color;

	color = 0;
	y = 0;
	x = 0;
	data->sq_size_x = MAP_WIDTH / data->map->width;
	data->sq_size_y = MAP_HEIGHT / data->map->height;
	while(y < MAP_HEIGHT && (y / data->sq_size_y) < data->map->height)
	{
		while (x < MAP_WIDTH && (x / data->sq_size_x) < data->map->width)
		{
			//printf("y: %d, x: %d\n", y / data->sq_size_y, x / data->sq_size_x);
			color = data->map->map[y / data->sq_size_y][x / data->sq_size_x] == '1';
			if (color)
				mlx_put_pixel(data->img_map, x, y, 0xFFFFFFFF);
			else
				mlx_put_pixel(data->img_map, x, y, 0x000000FF);
			x++;
		}
		x = 0;
		y++;
	}
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
	ft_print_minimap(&data);
	world_builder(&data);
	raycast(&data);
	mlx_image_to_window(data.mlx, data.img_bg, 0, 0);
	mlx_image_to_window(data.mlx, data.img_world, 0, 0);
	mlx_image_to_window(data.mlx, data.img_map, 0, 0);
	mlx_image_to_window(data.mlx, data.img_p, data.player.x - 4, data.player.y - 4);
	mlx_image_to_window(data.mlx, data.img_h, 0, 0);
	mlx_key_hook(data.mlx, &ft_key_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
