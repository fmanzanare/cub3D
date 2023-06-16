#include "../../includes/cub3D.h"

int	map[][8] =
{
	{1,1,1,1,1,1,1,1,},
	{1,0,1,0,0,0,0,1,},
	{1,0,1,0,0,0,0,1,},
	{1,0,1,0,0,0,0,1,},
	{1,0,0,0,0,0,0,1,},
	{1,0,0,0,0,1,0,1,},
	{1,0,0,0,0,0,0,1,},
	{1,1,1,1,1,1,1,1,},
};

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
		// printf("dx: %f, dy: %f, x: %f, y: %f, alpha: %f\n", data->player.dx, data->player.dy,
		// 	data->player.x, data->player.y, data->player.alpha);
}


int	is_wall(double py, double px) {
	int	x;
	int	y;

	x = (int)px /(MAP_WIDTH / MAP_X);
	y = (int)py /(MAP_HEIGHT / MAP_Y);
	return map[y][x];
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_rc	*data;
	int	t;

	t = -1;
	data = (t_rc *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
	{
		mlx_terminate(data->mlx);
		exit(0);
	}
	if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (!is_wall(data->player.y, data->player.x + data->player.dx))
			data->player.x += data->player.dx;
		if (!is_wall(data->player.y + data->player.dy, data->player.x))
			data->player.y += data->player.dy;
		data->img_p->instances[0].x = data->player.x;
		data->img_p->instances[0].y = data->player.y;
	}
	if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (!is_wall(data->player.y, data->player.x - data->player.dx))
			data->player.x -= data->player.dx;
		if (!is_wall(data->player.y - data->player.dy, data->player.x))
			data->player.y -= data->player.dy;
		data->img_p->instances[0].x = data->player.x;
		data->img_p->instances[0].y = data->player.y;
	}
	if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (!is_wall(data->player.y, data->player.x + data->player.dy))
			data->player.x += data->player.dy ;
		if (!is_wall(data->player.y - data->player.dx, data->player.x))
			data->player.y -= data->player.dx;
		data->img_p->instances[0].y = data->player.y;
		data->img_p->instances[0].x = data->player.x;
	}
	if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (!is_wall(data->player.y, data->player.x - data->player.dy))
			data->player.x -= data->player.dy;
		if (!is_wall(data->player.y + data->player.dx, data->player.x))
			data->player.y += data->player.dx;
		data->img_p->instances[0].y = data->player.y;
		data->img_p->instances[0].x = data->player.x;
	}
	// cabeza del jugador
	ft_rotation(keydata, data);
	memset(data->img_h->pixels, 0,data->img_h->width * data->img_h->height * 4 );
	while (t++ < MAP_WIDTH && !is_wall(data->player.y + 2 + t * (data->player.dy/MULT_DELTA), data->player.x + 2 + t * (data->player.dx/MULT_DELTA)))
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
	// p = 0; // iterador
	// pointer = (int *)data->img_h->pixels;
	// while ((unsigned int)p < data->img_h->width * data->img_h->height)
	// 	pointer[p++] = 0xf549b0ff;
}

void	ft_init(t_rc *data)
{
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
	int	mp;
	int	pixel;
	int	color;
	int	sq_size_x;
	int	sq_size_y;

	pixel = 0;
	color = 0;
	y = 0;
	x = 0;
	mp = 0;
	sq_size_x = MAP_WIDTH / MAP_X;
	sq_size_y = MAP_HEIGHT / MAP_Y;
	while(y < MAP_HEIGHT)
	{
		while (x < MAP_WIDTH)
		{
			color = map[y / sq_size_y][x / sq_size_x];
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
	data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!data.mlx)
		return (EXIT_FAILURE);
	ft_init(&data);
	ft_print_minimap(&data);
	mlx_image_to_window(data.mlx, data.img_map, 0, 0);
	mlx_image_to_window(data.mlx, data.img_p, data.player.x - 4, data.player.y - 4);
	mlx_image_to_window(data.mlx, data.img_h, 0, 0);
	mlx_key_hook(data.mlx, &ft_key_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
