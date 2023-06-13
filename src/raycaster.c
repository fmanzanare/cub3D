#include "../includes/cub3D.h"

int	map[][8] =
{
	{1,1,1,1,1,1,1,1,},
	{1,0,1,0,0,0,0,1,},
	{1,0,1,0,0,0,0,1,},
	{1,0,1,0,0,0,0,1,},
	{1,0,0,0,0,0,0,1,},
	{1,0,0,0,0,1,0,1,},
	{1,0,0,0,0,0,0,1,},
	{1,1,1,1,1,1,1,1,}
};

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_rc	*data;

	data = (t_rc *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
	{
		mlx_terminate(data->mlx);
		exit(0);
	}
	else if (keydata.key == MLX_KEY_UP
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		data->img_p->instances[0].y -= 10;
	else if (keydata.key == MLX_KEY_DOWN
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		data->img_p->instances[0].y += 10;
	else if (keydata.key == MLX_KEY_LEFT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		data->img_p->instances[0].x -= 10;
	else if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		data->img_p->instances[0].x += 10;
}

void	ft_init_minimap(t_rc *data)
{
	int	*pointer;
	int	p;

	p = 0;
	data->img_p = mlx_new_image(data->mlx, P_SIZE, P_SIZE);
	data->map_size = 8;
	memset(data->img_p->pixels, 255, data->img_p->width * data->img_p->height * 4);
	pointer = (int *)data->img_p->pixels;
	while ((unsigned int)p < data->img_p->width * data->img_p->height)
		pointer[p++] = 0xFF00FFFF;
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
	data->img_map = mlx_new_image(data->mlx, MAP_WIDTH, MAP_HEIGHT);
	memset(data->img_map->pixels, 255, data->img_map->width * data->img_map->height * 4);
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

int32_t	main(void)
{
	t_rc		data;

	data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!data.mlx)
		return (EXIT_FAILURE);
	ft_init_minimap(&data);
	ft_print_minimap(&data);
	mlx_image_to_window(data.mlx, data.img_map, 0, 0);
	mlx_image_to_window(data.mlx, data.img_p, 120, 150);
	mlx_key_hook(data.mlx, &ft_key_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
